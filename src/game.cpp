#include <algorithm> //
#include <stdexcept>

#include "player.hpp"
#include "dealer.hpp"
#include "game.hpp"


Game::Game(Rules &r, int numDecks, bool b) : rules(r), betting(b) {
    Shoe shoe(numDecks);
}

void Game::playRound() {
    DEBUG_PRINT("Starting round");
    if (shoe.cutCardReached(rules.deckPenetration)) shoe.initDeck();
    if (betting) bet();
    deal();
    //Short circuiting
    bool insurance = rules.insurance && betting && checkInsurance();
    bool blackjack = checkBlackjack();

    if(blackjack) DEBUG_PRINT("Dealer blackjack");
    if(insurance) DEBUG_PRINT("Insurance offered");
    DEBUG_PRINT("Dealer upcard: " + std::to_string(dealer.upCard()));
    if (!blackjack) {
        int i = 0;
        for (auto &player : players) {
            i++;
            DEBUG_PRINT("Player " + std::to_string(i) + "'s starting hand: " + player.toString() 
                        + " with total: " + std::to_string(player.getSum()));
            playHand(player);
            DEBUG_PRINT("Player " + std::to_string(i) + "'s ending hand: " + player.toString() 
                        + " with total: " + std::to_string(player.getSum()));
        }
        DEBUG_PRINT("Dealer's starting hand: " + dealer.toString() + " with total: " 
                    + std::to_string(dealer.getSum()));
        playDealer();
        DEBUG_PRINT("Dealer's ending hand: " + dealer.toString() + " with total: " 
                    + std::to_string(dealer.getSum()));
        i = 0;
        for (auto &player : players) {
            i++;
            setResult(player);
            DEBUG_PRINT("Player " + std::to_string(i) + "'s result: " + toString(player.won));
        }
    }

    cleanupRound(blackjack, insurance);
    DEBUG_PRINT("End round");
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
        if (std::find(all.begin(), all.end(), a) != all.end()) {
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
    //Hit when sum is less than 17 OR equal to 17 AND soft AND NOT stand soft 17
    while (dealer.getSum() < 17 || 
          (!rules.s17 && dealer.getSum() == 17 && dealer.isSoft())) {
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
    int card = shoe.draw(h);
    DEBUG_PRINT("Dealing " + std::to_string(card));
    return card;
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
    //Only do this for undetermined results, i.e., don't change LOSS or BLACKJACK
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