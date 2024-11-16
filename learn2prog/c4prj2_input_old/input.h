#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>
#include "deck.h"
#include "future.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc);
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc);
void process_token(char *token_value, char *token_suit, deck_t *hand, future_cards_t *fc);

#endif
