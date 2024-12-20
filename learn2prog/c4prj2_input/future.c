#include "future.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
    if (fc == NULL) {
        perror("Please input the correct future_cards pointer\n");
        return;
    }

    if (index >= fc->n_decks) {
        deck_t *temp_decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));
        if (temp_decks == NULL) {
            perror("Failed to allocate memory for more decks\n");
            return;
        }
        fc->decks = temp_decks;

        //initialize the new decks
        for (int i = fc->n_decks; i <= index; i++) {
            fc->decks[i].cards = NULL;
            fc->decks[i].n_cards = 0;
        }

        fc->n_decks = index + 1;
    }

    if (fc->decks[index].cards == NULL) {
        fc->decks[index].cards = malloc(sizeof (card_t *));
        fc->decks[index].n_cards = 0;
    }

    int card_count = fc->decks[index].n_cards;
    card_t **temp_cards = realloc(fc->decks[index].cards, (card_count + 1) * sizeof (card_t *));
    if (temp_cards == NULL) {
        perror("Failed to allocate memory for future card pointer\n");
        return;
    }
    fc->decks[index].cards = temp_cards;
    fc->decks[index].cards[card_count] = ptr;
    fc->decks[index].n_cards = card_count + 1;


}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    if (deck->n_cards < fc->n_decks) {
        perror("Cards in deck is not enough to fill the future card\n");
        return;
    }

    for (int i = 0; i < fc->n_decks; i++) {
        if (fc->decks[i].cards == NULL || fc->decks[i].n_cards == 0) {
            continue;
        }
        card_t *card_to_fill = deck->cards[i];
        for (int j = 0; j < fc->decks[i].n_cards; j++) {
            *(fc->decks[i].cards[j]) = *card_to_fill;
        }
    }

}

void clean_future_card(future_cards_t *fc) {
    for (int i = 0; i < fc->n_decks; i++) {
        if (fc->decks[i].cards == NULL || fc->decks[i].n_cards == 0) {
            continue;
        }
        for (int j = 0; j < fc->decks[i].n_cards; j++) {
            fc->decks[i].cards[j]->suit = 0;
            fc->decks[i].cards[j]->value = 0;
        }
    }
}

void free_future_card(future_cards_t *fc) {
    for (int i = 0; i < fc->n_decks; i++) {
        deck_t *curr_deck = fc->decks + i;
        free(curr_deck->cards);

    }
    free(fc->decks);
    free(fc);

}


