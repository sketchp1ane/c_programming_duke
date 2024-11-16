#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "future.h"

void add_future_card(future_cards_t *fc, size_t index, card_t *ptr) {
    int length_decks = fc->n_decks;

    // If the requested index is beyond the current number of decks, resize the array
    if (index >= length_decks) {
        // Resize the array of decks to accommodate the new index
        deck_t *temp_decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));
        if (temp_decks == NULL) {
            perror("Failed to allocate memory for more decks\n");
            return;
        }
        fc->decks = temp_decks;  // Only update fc->decks if realloc is successful

        // Initialize the new deck at the specified index
        fc->decks[index].n_cards = 0;
        fc->decks[index].cards = malloc(sizeof(card_t *));
        if (fc->decks[index].cards == NULL) {
            perror("Failed to allocate memory for first card in a deck\n");
            return;
        }
        fc->n_decks = index + 1;  // Update the number of decks
    }

    // Add the card to the specific future card deck
    int length_cards = fc->decks[index].n_cards;
    card_t **temp_cards = realloc(fc->decks[index].cards, (length_cards + 1) * sizeof(card_t *));
    if (temp_cards == NULL) {
        perror("Failed to allocate memory for more card pointers\n");
        return;
    }
    fc->decks[index].cards = temp_cards;  // Only update if realloc is successful

    fc->decks[index].cards[length_cards] = ptr;  // Add the card to the deck
    fc->decks[index].n_cards++;  // Increment the card count for the deck
}


void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    for (int i = 0; i < fc->n_decks; i++) {
        if ((fc->decks + i)->cards == NULL || (fc->decks + i)->n_cards == 0) {
            continue;
        }
        unsigned valueForThisDeck = deck->cards[i]->value;
        suit_t suitForThisDeck = deck->cards[i]->suit;
        for (int j = 0; j < (fc->decks + i)->n_cards; j++) {
            (fc->decks + i)->cards[j]->value = valueForThisDeck;
            (fc->decks + i)->cards[j]->suit = suitForThisDeck;
        }
    }
}

void print_future_cards(future_cards_t * fc) {
    for (int i = 0; i < fc->n_decks; i++) {
        print_hand(fc->decks + i);
    }
}
