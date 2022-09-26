#pragma once

#include "hand.hpp"

class Dealer : public Hand {
public:
    int holeCard();
    int upCard();
    //int flipHoleCard();
};