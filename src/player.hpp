#pragma once
#include <vector>

#include "hand.hpp"
#include "shoe.hpp"

enum result {WIN, LOSS, PUSH, BLACKJACK};

enum action {STAND, HIT, DOUBLE, SPLIT, SURRENDER};

typedef std::vector<action> actionList;

class Player : public Hand {
    double bankroll = 0;
    double bet = 0;
    double insurance = 0;
public:
    int won = PUSH;

    Player() {};
    Player(double b) : bankroll(b) {};
    void clear();

    virtual action getAction(const Shoe &);
    actionList possibleActions();

    double makeBet(const Shoe &);
    double modifyBet(double);
    void resolveBet();

    double makeBetInsurance(const Shoe &);
    void resolveInsurance(bool, double);

    //Testing
    void setHand(const std::vector<int> &);
};