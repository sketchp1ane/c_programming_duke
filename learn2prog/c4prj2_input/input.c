#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    deck_t **hands = malloc(sizeof (deck_t *));
    size_t hand_count = 0;

    char *currLine = NULL;
    size_t sz = 0;
    ssize_t n_read = 0;

    while ((n_read = getline(&currLine, &sz, f)) != -1) {
        // 去掉行末的换行符
        if (currLine[n_read - 1] == '\n') {
            currLine[n_read - 1] = '\0';
        }

        deck_t *hand = hand_from_string(currLine, fc);
        if (hand == NULL) {
            fprintf(stderr, "Failed to parse the hand: %s\n", currLine);
            return NULL;
        }

        deck_t **temp_hands = realloc(hands, (hand_count + 1) * sizeof(deck_t *));
        if (temp_hands == NULL) {
            perror("Failed to allocate memory for more hands\n");
            return NULL;
        }
        hands = temp_hands;

        hands[hand_count] = hand;
        hand_count++;
        *n_hands = hand_count;


    }
    free(currLine);

    return hands;


}


deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t *hand = malloc(sizeof (deck_t));
    if (hand == NULL) {
        perror("Failed to allocate memory for a hand\n");
        return NULL;
    }
    hand->cards = NULL;
    hand->n_cards = 0;

    char *str_copy = strdup(str);
    char *token = strtok(str_copy, " ");

    while (token != NULL) {
        if (token[0] == '?') {
            card_t *placeholder = add_empty_card(hand);
            add_future_card(fc, atoi(&token[1]), placeholder);
        } else {
            card_t card = card_from_letters(token[0], token[1]);
            add_card_to(hand, card);
        }
        token = strtok(NULL, " ");
    }

    free(str_copy);

    if (hand->n_cards < 5) {
        fprintf(stderr, "At least 5 cards in a hand\n");
        free(hand);
        return NULL;
    }

    return hand;




}

void free_input (deck_t **hands, size_t n_hands) {
    for (size_t i = 0; i < n_hands; i++) {
        free_deck(hands[i]);
    }

    free(hands);

}

