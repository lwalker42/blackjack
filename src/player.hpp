#pragma once

#include "hand.hpp"
#include "shoe.hpp"

class Player : public Hand {
    double bankroll;
public:
    Player();
    Player(double b) : bankroll(b) {};
    bool draw(int);
    void clear();
    int makeBet(const Shoe&);
};