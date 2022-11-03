#include <random>
#include <vector>

#include "player.hpp"


void Player::clear() {
    Hand::clear();
    bet = 0;
    won = PUSH;
    insurance = 0;
    splitHands.clear();
}

action Player::getAction(const Shoe &, int upCard, Rules &rules) {
    actionList actions = possibleActions(rules);
    
    static std::random_device rd;
    static std::mt19937_64 g(rd());
    //20 is lowest common multiple of 5, 4, 2
    static std::uniform_int_distribution<> dist(1, 20);
    return actions[dist(g) % actions.size()];
}

actionList Player::possibleActions(Rules &rules) {
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


//Returns true if hand was successfully split
bool Player::splitHand() {
    //Not 2 cards, or different cards, or insufficient funds
    if (cards.size() != 2 || cards[0] != cards[1] || bankroll < bet)
        return false;

    Player newHand(bankroll, splitHands);
    newHand.makeBet(bet);
    newHand.draw(cards[1]);
    cards.pop_back();
    splitHands.push_back(newHand);
    return true;
}

int Player::numHands() {
    return 1 + splitHands.size();
}

Player &Player::getHand(int i) {
    return splitHands[i];
}


double Player::makeBet() {
    return makeBet(1);
}

double Player::makeBet(double bet) {
    if (bet >= bankroll) {
        bet = 0;
        return 0;
    }

    bankroll -= bet;
    return bet;
}

//Multiple of current bet to change to
//Returns true if double (or other increase) was succesful
bool Player::modifyBet(double d) {
    if (bet * (d - 1) < bankroll) {
        return false;
    }
    bankroll += bet;
    bet *= d;
    bankroll -= bet;
    return true;
}

void Player::resolveBet(double blackjackPayout) {
    switch (won) {
    case BLACKJACK:
        bankroll += bet * (1 + blackjackPayout);
        break;
    case WIN:
        bankroll += bet * 2;
        break;
    case LOSS:
        break;
    case PUSH:
        bankroll += bet;
    }
}


double Player::makeBetInsurance() {
    static std::random_device rd;
    static std::mt19937_64 g(rd());
    static std::uniform_int_distribution<> dist(0, 1);
    return dist(g) ? bet/2 : 0;
    //return bet/2;
}

void Player::resolveInsurance(bool dealerBJ, double payout) {
    if (dealerBJ)
        bankroll += insurance * payout;
    else
        bankroll -= insurance;
}



void Player::setHand(const std::vector<int> &newCards) {
    cards.clear();
    for (int card : newCards) {
        cards.push_back(card);
    }
}