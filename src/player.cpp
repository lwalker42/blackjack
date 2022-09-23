#include "player.hpp"

bool Player::draw(int c) {
    cards.push_back(c);
    return true;
}

void Player::clear() {
    cards.clear();
}

int Player::makeBet(const Shoe &shoe) {
    return 0;
}