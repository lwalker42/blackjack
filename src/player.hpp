#pragma once
#include <vector>
#include <string>

#include "rules.hpp"
#include "hand.hpp"
#include "shoe.hpp"
enum result {WIN, LOSS, PUSH, BLACKJACK};

std::string toString(result);

enum action {STAND, HIT, DOUBLE, SPLIT, SURRENDER};

typedef std::vector<action> actionList;
class Player;
typedef std::vector<Player> splits;

class Player : public Hand {
    double bankroll = 0;
    double bet = 0;
    double insurance = 0;
    splits splitHands;
public:
    result won = PUSH;

    Player() {};
    Player(double &b) : bankroll(b) {};
    Player(double &b, splits &hands) : bankroll(b), splitHands(hands) {};
    void clear();

    virtual action getAction(const Shoe &, int, Rules &);
    actionList possibleActions(Rules &);

    bool splitHand();
    int numHands();
    Player &getHand(int);
    

    double makeBet();
    double makeBet(double);
    bool modifyBet(double);
    void resolveBet(double);

    double makeBetInsurance();
    void resolveInsurance(bool, double);
};