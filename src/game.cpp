#include <algorithm> //
#include <stdexcept>

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
    bool insurance = rules.insurance && betting && checkInsurance();
    bool blackjack = checkBlackjack();

    if (!blackjack) {
        for (auto &player : players) {
            playHand(player);
        }
        playDealer();
        for (auto &player : players) {
            setResult(player);
        }
    }

    cleanupRound(blackjack, insurance);
}

result Game::playHand(Player &p) {
    Player current = p;
    int i = -1;
    while (i < p.numHands()) {
        current = i == -1 ? p : p.getHand(i);
        //Split hands have 1 card
        if (current.size() == 1) {
            if (current.getSum() == 11) {
            /*Handle Resplit aces later*/
                dealOne(current);
                i++;
                continue;
            } else {
                dealOne(current);
            }
        }

        action a = p.getAction(shoe, dealer.upCard(), rules);
        actionList all = current.possibleActions(rules);
        if (std::any_of(all.begin(), all.end(), a)) {
            if (a == STAND) {
                i++;
            } else if (a == HIT) {
                dealOne(current);
                if (current.bust()) {
                    current.won = LOSS;
                    i++;
                }
            } else if (a == DOUBLE) {
                if (!current.modifyBet(2)) {
                    throw std::runtime_error("Insufficient funds to double");
                }
                dealOne(current);
                i++;
                if (current.bust()) {
                    current.won = LOSS;
                }
            } else if (a == SPLIT) {
                if(!current.splitHand()) {
                    throw std::runtime_error("Insufficient funds to split");
                }
            } else if (a == SURRENDER) {
                current.modifyBet(.5);
                current.won = LOSS;
            }

        } else {
            throw std::invalid_argument("Invalid action");
        }
    }
    return p.won;
}


int Game::playDealer() {
    //Stand when sum greater than 17 OR equal to 17 and stand soft 17
    //OR hit soft 17 and equal to 17 and hard total
    while (dealer.getSum() > 17 ||
           rules.s17 && dealer.getSum() == 17 ||
           dealer.getSum() == 17 && !dealer.isSoft()) {
        dealOne(dealer);
    }
    return dealer.getSum();
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
        player.makeBet();
    }
}

/*Returns true if dealer has blackjack
 */
bool Game::checkBlackjack() {
    bool dealerBJ = dealer.getSum() == 21;
    
    for (auto &player : players) {
        if (player.getSum() == 21) {
            player.won = dealerBJ ? PUSH : BLACKJACK;
        } else if (dealerBJ) {
            player.won = LOSS;
        }
    }
    return dealerBJ;
}

//Insurance and even money are the same
bool Game::checkInsurance() {
    if (dealer.upCard() == 11) {
        for (auto &player : players) {
            player.makeBetInsurance();
        }
        return true;
    }
    return false;
}

result Game::setResult(Player &p) {
    //Only do this for undetermined results, i.e., not LOSS or BLACKJACK
    if (p.won == PUSH) {
        if (dealer.bust() || p.getSum() > dealer.getSum())
            p.won = WIN;
        else if (p.getSum() < dealer.getSum())
            p.won = LOSS;
    }
    return p.won;
}


void Game:: cleanupRound(bool blackjack, bool insurance) {
    dealer.clear();
    for (auto &player : players) {
        if (betting) {
            player.resolveBet(rules.blackjackPayout);
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