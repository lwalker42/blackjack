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
    checkBlackjack();
}

void Game::deal() {
    for (auto &player : players) {
        for (int i = 0; i < 2; i++) {
            shoe.draw(player);
        }
    }
    for (int i = 0; i < 2; i++) {
        //Handle counting here later
        shoe.draw(dealer);
    }
}

int Game::dealOne(Hand &h) {
    shoe.draw(h);
    return 0;
}

void Game::bet() {
    for (auto &player : players) {
        player.makeBet(shoe);
    }
}

void Game::checkBlackjack() {
    bool dealerBJ = 
    if (dealer.sum() == 21) {

    }
    for (auto &player : players) {
        if (player.sum() == 21) {

        }
    }
}

void Game::cleanupRound() {
    dealer.clear();
    for (auto &player : players) {
        player.clear();
    }
    //Do something here for bets
}

void Game::addPlayer(const Player &p) {
    players.push_back(p);
}

void Game::addDealer(const Dealer &d) {
    dealer = d;
}