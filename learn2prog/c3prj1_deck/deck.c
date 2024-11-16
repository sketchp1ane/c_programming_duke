#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"

// 打印手牌中的每张卡
void print_hand(deck_t * hand) {
    card_t ** cards = hand->cards;
    for (int i = 0; i < hand->n_cards; i++) {
        card_t card = *cards[i];  // 修正的访问方式
        print_card(card);
        printf(" ");
    }

}

// 检查牌组中是否包含指定的卡
int deck_contains(deck_t * d, card_t c) {
    card_t ** cards = d->cards;
    for (int i = 0; i < d->n_cards; i++) {
        card_t card = *cards[i];  // 修正的访问方式
        if (card.value == c.value && card.suit == c.suit) {
            return 1;
        }
    }
    return 0;
}

// 随机洗牌
void shuffle(deck_t * d) {
    //srandom(time(NULL)); // Seed the pseudo-random number generator

    for (size_t i = d->n_cards - 1; i > 0; i--) {
        size_t j = random() % (i + 1); // Generate a pseudo-random index between 0 and i

        // Swap cards[i] and cards[j]
        card_t * temp = d->cards[i];
        d->cards[i] = d->cards[j];
        d->cards[j] = temp;
    }
}


// 检查牌组是否包含完整的 52 张牌
void assert_full_deck(deck_t * d) {
    assert(d->n_cards == 52);
    for (size_t i = 0; i < 52; i++) {
        assert(deck_contains(d, card_from_num(i)));
    }
}

void add_card_to(deck_t * deck, card_t c) {
    int length = deck->n_cards;
    deck->cards = realloc(deck->cards, (length + 1) * sizeof (card_t *));
    if (deck->cards == NULL) {
        perror("Failed to allocate memory for new card pointer\n");
        return;
    }
    deck->cards[length] = malloc(sizeof (card_t));
    if (deck->cards[length] == NULL) {
        perror("Failed to allocate memory for new card entity\n");
        return;
    }
    deck->cards[length]->value = c.value;
    deck->cards[length]->suit = c.suit;
    deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck) {
    int length = deck->n_cards;
    deck->cards = realloc(deck->cards, (length + 1) * sizeof (card_t *));
    if (deck->cards == NULL) {
        perror("Failed to allocate memory for empty card\n");
        return NULL;
    }
    card_t * emptyCard = malloc(sizeof (card_t));
    if (emptyCard == NULL) {
        perror("Failed to allocate memory for a card, value = 0, suit = 0\n");
        return NULL;
    }
    emptyCard->value = 0;
    emptyCard->suit = 0;
    deck->cards[length] = emptyCard;
    deck->n_cards++;
    return emptyCard;
}

deck_t *make_deck_exclude(deck_t * excluded_cards) {
    deck_t *deck_exclude = malloc(sizeof(deck_t));
    deck_exclude->cards = NULL;
    deck_exclude->n_cards = 0;
    for (size_t i = 0; i < 52; i++) { // Pasas por las 52 cartas pero solo vas a añadir las que no estén
        card_t possible_card = card_from_num(i);
        if (deck_contains(excluded_cards, possible_card) == 0) {
            add_card_to(deck_exclude, possible_card);
        }
    }
    return deck_exclude;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
    deck_t * cards_from_all_hands = malloc(sizeof (deck_t));
    if (cards_from_all_hands == NULL) {
        perror("Failed to allocate memory for cards_from_all_hands\n");
        return NULL;
    }
    cards_from_all_hands->cards = malloc(sizeof (card_t *));
    if (cards_from_all_hands == NULL) {
        perror("Failed to allocate memory for the first card in cards_from_all_hands\n");
        return NULL;
    }
    cards_from_all_hands->n_cards = 0;
    for (int i = 0; i < n_hands; i++) {
        for (int j = 0; j < hands[i]->n_cards; j++) {
            add_card_to(cards_from_all_hands, *hands[i]->cards[j]);
        }
    }

    deck_t * result = make_deck_exclude(cards_from_all_hands);
    free(cards_from_all_hands);
    return result;

}

void free_deck(deck_t * deck) {
    assert(deck != NULL);
    for (int i = 0; i < deck->n_cards; i++) {
        if (deck->cards[i] == NULL) {
            continue;
        }
        free(deck->cards[i]);
    }
    if (deck->cards != NULL) {
        free(deck->cards);
    }

    free(deck);

}

