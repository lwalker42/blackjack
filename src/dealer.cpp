#include "dealer.hpp"

int Dealer::holeCard() {
    return cards.size() > 0 ? cards[0] : -1;
}

int Dealer::upCard() {
    return cards.size() > 1 ? cards[1] : -1;
}

