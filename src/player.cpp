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
    actionList actions = possibleActions();
    
    static std::random_device rd;
    static std::mt19937_64 g(rd());
    //20 is lowest common multiple of 5, 4, 2
    static std::uniform_int_distribution<> dist(1, 20);
    return actions[dist(g) % actions.size()];
    //int c = std::rand();
}

actionList Player::possibleActions() {
    //Double and surrender available
    if (cards.size() == 2) {
        //Split available
        if (cards[0] == cards[1]) {
            return {STAND, HIT, DOUBLE, SPLIT, SURRENDER};
        } else {
            return {STAND, HIT, DOUBLE, SURRENDER};
        }
    } else {
        return {STAND, HIT};
    }
}


//TODO: limit overbetting bankroll, especially in special cases (doubling, splitting)
double Player::makeBet(const Shoe &shoe) {
    if (bet >= bankroll) {
        bet = 0;
        return 0;
    }

    bankroll -= bet;

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