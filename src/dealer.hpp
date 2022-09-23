#pragma once

#include "hand.hpp"

class Dealer : public Hand {
    int holeCard = -1;
public:
    bool draw(int);
    void clear();
    int holeCard();
    int upCard();
    int flipHoleCard();
};