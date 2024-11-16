#include <stdio.h>
#include "cards.h"

int main() {
    card_t c1 = { .value = 14, .suit = SPADES };  // Aces of Spades
    card_t c2 = { .value = 10, .suit = DIAMONDS };  // 10 of Diamonds
    card_t c3 = { .value = 13, .suit = CLUBS };  // King of Clubs

    printf("Testing print_card:\n");
    print_card(c1);  // 应该输出 As
    printf("\n");
    print_card(c2);  // 应该输出 0d
    printf("\n");
    print_card(c3);  // 应该输出 Kc
    printf("\n");

    return 0;
}
