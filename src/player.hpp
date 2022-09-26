#pragma once

#include "hand.hpp"
#include "shoe.hpp"

#define WIN 1
#define LOSS -1
#define PUSH 0


class Player : public Hand {
    double bankroll = 0;
    double bet = 0;
    double insurance = 0;
public:
    int won = PUSH;

    Player() {};
    Player(double b) : bankroll(b) {};
    void clear();
    double makeBet(const Shoe &);
    double modifyBet(double);
    double makeBetInsurance(const Shoe &);
    void resolveInsurance(bool, double);
    void resolveBet();
};