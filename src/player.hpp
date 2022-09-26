#pragma once

#include "hand.hpp"
#include "shoe.hpp"

enum result {WIN, LOSS, PUSH};

enum action {STAND, HIT, DOUBLE, SPLIT, SURRENDER};

class Player : public Hand {
    double bankroll = 0;
    double bet = 0;
    double insurance = 0;
public:
    int won = PUSH;

    Player() {};
    Player(double b) : bankroll(b) {};
    void clear();

    action getAction(const Shoe &);

    double makeBet(const Shoe &);
    double modifyBet(double);
    void resolveBet();

    double makeBetInsurance(const Shoe &);
    void resolveInsurance(bool, double);

    //Testing
    void setHand(const std::vector<int> &);
};