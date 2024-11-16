#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
    if (argc != 2 && argc != 3) {
        perror("Usage: ./poker file_name time_to_perform(optional)\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open the file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    size_t n_hands = 0;
    future_cards_t *fc = malloc(sizeof (future_cards_t));
    if (fc == NULL) {
        perror("Failed to allocate memory for future cards\n");
        return EXIT_FAILURE;
    }
    fc->decks = NULL;
    fc->n_decks = 0;
    deck_t **hands = read_input(file, &n_hands, fc);
    fclose(file);

    deck_t *remain_deck = build_remaining_deck(hands, n_hands);

    int time_count = 0;
    if (argc == 2) {
        time_count = 10000;
    } else {
        time_count = atoi(argv[2]);
    }
    // n_hands index represents there was a tie;
    int* winner_count = (int*)calloc(n_hands + 1, sizeof(int));
    if (winner_count == NULL) {
        perror("Failed to allocate memory for winner count array\n");
        return EXIT_FAILURE;
    }
    int time_count_copy = time_count;
    while (time_count_copy--) {
        int tie_flag = 1;
        shuffle(remain_deck);
        future_cards_from_deck(remain_deck, fc);


        int winner_index = 0;
        for (int i = 1; i < n_hands; i++) {
            int result = compare_hands(hands[winner_index], hands[i]);
            if (result != 0) {
                tie_flag = 0;
            }
            if (result < 0) {
                winner_index = i;
            }
        }

        if (tie_flag == 1) {
            winner_count[n_hands]++;
        } else {
            winner_count[winner_index]++;
        }
    }

    for (size_t i = 0; i < n_hands; i++) {
        printf("Hand %zu won %u / %u times (%.2f%%)\n", i, winner_count[i], time_count, (double) winner_count[i] / time_count * 100);
    }

    printf("And there were %u ties\n", winner_count[n_hands]);

    free(winner_count);
    free_future_card(fc);
    free_deck(remain_deck);
    free_input(hands, n_hands);






    return EXIT_SUCCESS;
}
