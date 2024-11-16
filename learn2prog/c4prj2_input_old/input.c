#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "input.h"

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    assert(f != NULL);

    deck_t ** hands = malloc(sizeof (deck_t *));
    if (hands == NULL) {
        perror("Failed to allocate memory for first deck(hand) pointer\n");
        return NULL;
    }

    ssize_t length_of_line = 0;
    char *currLine = NULL;
    size_t sz = 0;
    while ((length_of_line = getline(&currLine, &sz, f)) >= 0) {
        hands = realloc(hands, (*n_hands + 1) * sizeof (deck_t *));
        currLine[length_of_line - 1] = '\0';
        hands[*n_hands] = hand_from_string(currLine, fc);
        (*n_hands)++;

    }
    free(currLine);
    return hands;

}



void process_token(char *token_value, char *token_suit, deck_t *hand, future_cards_t *fc) {
    if (*token_value == '?') {
        // 如果是 '?' 卡牌，调用 add_empty_card 和 add_future_card
        card_t *empty_card = add_empty_card(hand);
        add_future_card(fc, atoi(token_suit), empty_card);
    } else {
        // 否则，根据字符生成卡牌并添加到手牌中
        card_t card = card_from_letters(*token_value, *token_suit);
        add_card_to(hand, card);
    }
}




deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t * hand = malloc(sizeof (deck_t));
    if (hand == NULL) {
        perror("Failed to allocate memory for a hand\n");
        return NULL;
    }

    hand->n_cards = 0;
    hand->cards = malloc(sizeof (card_t *));
    if (hand->cards == NULL) {
        perror("Failed to allocate memory for first card pointer in one hand\n");
        return NULL;
    }

    char *copy = strdup(str);
    strcpy(copy, str);
    char *token_value = strtok(copy, " ");



    while (token_value != NULL) {
        char *token_suit = token_value + 1;
        process_token(token_value, token_suit, hand, fc);
        token_value = strtok(NULL, " ");

    }

    return hand;







}
