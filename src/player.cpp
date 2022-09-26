#include <random>
#include <vector>

#include "player.hpp"


void Player::clear() {
    Hand::clear();
    bet = 0;
    won = PUSH;
    insurance = 0;
}
action Player::getAction(const Shoe &) {
    std::vector<action> actions;
    //Double and surrender available
    if (cards.size() == 2) {
        //Split available
        if (cards[0] == cards[1]) {
            actions = {STAND, HIT, DOUBLE, SPLIT, SURRENDER};
        } else {
            actions = {STAND, HIT, DOUBLE, SURRENDER};
        }
    } else {
        actions = {STAND, HIT};
    }
    static std::random_device rd;
    static std::mt19937_64 g(rd());
    //20 is lowest common multiple of 5, 4, 2
    static std::uniform_int_distribution<> dist(1, 20);
    return actions[dist(g) % actions.size()];
    //int c = std::rand();
}


//TODO: limit overbetting bankroll, especially in special cases (doubling, splitting)
double Player::makeBet(const Shoe &shoe) {
    return bet;
}

double Player::modifyBet(double d) {
    bet *= d;
    return bet;
}

void Player::resolveBet() {
    switch (won) {
    case WIN:
        bankroll += bet;
        break;
    case LOSS:
        bankroll -= bet;
        break;
    case PUSH:
        break;
    }    
}


double Player::makeBetInsurance(const Shoe &shoe) {
    return 0;
    //return bet/2;
}

void Player::resolveInsurance(bool dealerBJ, double payout) {
    if (dealerBJ)
        bankroll += insurance * payout;
    else
        bankroll -= insurance;
}



void Player::setHand(const std::vector<int> & newCards) {
    cards.clear();
    for (int card : newCards) {
        cards.push_back(card);
    }
}