#include "dealer.hpp"

bool Dealer::draw(int c) {
    cards.push_back(c);
}

void Dealer::clear() {
    cards.clear();
    holeCard = -1;
}

int Dealer::flipHoleCard() {
    cards.push_back(holeCard);
    return holeCard;
}
