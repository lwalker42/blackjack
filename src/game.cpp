#include <algorithm> //find

#include "player.hpp"
#include "dealer.hpp"
#include "game.hpp"


Game::Game(Rules &r, bool b) : rules(r), betting(b) {
    Shoe shoe;
}

void Game::playRound() {
    if (shoe.cutCardReached(rules.deckPenetration)) shoe.initDeck();
    if (betting) bet();
    deal();
    //Short circuiting
    bool insurance = rules.insurance && checkInsurance();
    bool blackjack = checkBlackjack();

    cleanupRound(blackjack, insurance);
}

int Game::playHand(Player &p) {

    return PUSH;
}



void Game::deal() {
    /*
    //Order of nested loop matters if deck penetration is 100%
    //But slower to access players vector multiple times
    for (int i = 0; i < 2; i++) {
        //Handle counting here later
        shoe.draw(dealer);
    }*/

    for (auto &player : players) {
        for (int i = 0; i < 2; i++) {
            dealOne(player);
        }
    }
    for (int i = 0; i < 2; i++) {
        //Handle counting here later
            dealOne(dealer);
    }
}

int Game::dealOne(Hand &h) {
    return shoe.draw(h);
}

void Game::bet() {
    for (auto &player : players) {
        player.makeBet(shoe);
    }
}

/*Returns true if dealer has blackjack
 */
bool Game::checkBlackjack() {
    bool dealerBJ = dealer.getSum() == 21;
    
    for (auto &player : players) {
        if (player.getSum() == 21) {
            player.won = dealerBJ ? PUSH : WIN;
            player.modifyBet(rules.blackjackPayout);
        } else if (dealerBJ) {
            player.won = LOSS;
        }
    }
    return dealerBJ;
}

//Insurance and even money are the same
bool Game::checkInsurance() {
    if (betting && dealer.upCard() == 11) {
        for (auto &player : players) {
            player.makeBetInsurance(shoe);
        }
    }
    return dealer.upCard() == 11;
}


void Game:: cleanupRound(bool blackjack, bool insurance) {
    dealer.clear();
    for (auto &player : players) {
        if (betting) {
            player.resolveBet();
            if (insurance) player.resolveInsurance(blackjack, 2);
        }
        player.clear();
    }
}

void Game::addPlayer(const Player &p) {
    players.push_back(p);
}

void Game::addDealer(const Dealer &d) {
    dealer = d;
}