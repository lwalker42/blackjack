#include "player.hpp"


void Player::clear() {
    Hand::clear();
    bet = 0;
    won = PUSH;
    insurance = 0;
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
