#include <algorithm> //
#include <stdexcept>

#include "player.hpp"
#include "dealer.hpp"
#include "game.hpp"


Game::Game(Rules &r, int numDecks, bool b) : rules(r), betting(b) {
    Shoe shoe(numDecks);
}

void Game::playRound() {
    DEBUG_PRINT("Starting round\n");
    if (shoe.cutCardReached(rules.deckPenetration)) shoe.initDeck();
    if (betting) bet();
    deal();
    //Short circuiting
    bool insurance = rules.insurance && betting && checkInsurance();
    bool blackjack = checkBlackjack();

    if(blackjack) DEBUG_PRINT("Dealer blackjack\n");
    if(insurance) DEBUG_PRINT("Insurance offered\n");
    DEBUG_PRINT("Dealer upcard: " + std::to_string(dealer.upCard()) + "\n\n");
    DEBUG_PRINT("");
    if (!blackjack) {
        int i = 0;
        for (auto &player : players) {
            i++;
            DEBUG_PRINT("Player " + std::to_string(i) + "'s starting hand: " + player.toString() 
                        + " with total: " + std::to_string(player.getSum()) + '\n');
            playHand(player);
            DEBUG_PRINT("\n\n");
        }
        DEBUG_PRINT("Dealer's starting hand: " + dealer.toString() + " with total: " 
                    + std::to_string(dealer.getSum()) + '\n');
        playDealer();
        DEBUG_PRINT("\nDealer's ending hand: " + dealer.toString() + " with total: " 
                    + std::to_string(dealer.getSum()) + (dealer.bust() ? " BUSTS" : "") + "\n\n");
        i = 0;
        for (auto &player : players) {
            i++;
            setResult(player);
            DEBUG_PRINT("Player " + std::to_string(i) + "'s result: " + '\n');
            for(int j = 0; j < player.numHands(); j++) {
                DEBUG_PRINT("Hand #" + std::to_string(j+1) + ": " + toString(player.getHand(j).won) + '\n');
            }
        }
    }

    cleanupRound(blackjack, insurance);
    DEBUG_PRINT("End round");
}

result Game::playHand(Player &p) {
    int i = 0;
    while (i < p.numHands()) {
        Player &current = p.getHand(i);
        //DEBUG_PRINT("i = " + std::to_string(i) + ", numHands() = " + std::to_string(current.numHands()) + ", current hand = " + current.toString() + "\t");
        DEBUG_PRINT("Hand # " + std::to_string(i+1) + ": ");
        if (current.won == BLACKJACK) {
            DEBUG_PRINT("Blackjack!\n");
            i++;
            continue;
        }
        //Split hands have 1 card
        if (current.size() == 1) {
            
            if (current.getSum() == 11) {
            /*Handle Resplit aces later*/
                DEBUG_PRINT("Ace gets 1 card ");
                i++;
            }
            dealOne(current);
            DEBUG_PRINT("Current hand: " + current.toString() + "\n");
            continue;
        }

        action a = current.getAction(shoe, dealer.upCard(), rules);
        actionList all = current.possibleActions(rules);
        DEBUG_PRINT("Player chooses to " + toString(a) + ". ");
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
                DEBUG_PRINT(std::to_string(current.numHands()) + " total hands\n");
                continue;
            } else if (a == SURRENDER) {
                i++;
                current.modifyBet(.5);
                current.won = LOSS;
            }

        } else {
            throw std::invalid_argument("Invalid action");
        }
        DEBUG_PRINT("Current hand: " + current.toString() + (current.bust() ? " BUSTS\n" : "\n"));
    }
    //DEBUG_PRINT("i = " + std::to_string(i) + " numHands() = " + std::to_string(current.numHands()) + '\t');
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
    int j = 0;
    for (auto &player : players) {
        j++;
        DEBUG_PRINT("Dealing Player " + std::to_string(j) + ": ");
        for (int i = 0; i < 2; i++) {
            dealOne(player);
        }
        DEBUG_PRINT("\n");
    }
    for (auto &player : players) {
        DEBUG_PRINT("Player hand: " + player.toString() + '\n');
    }

    DEBUG_PRINT("Dealing Dealer: ");
    for (int i = 0; i < 2; i++) {
        //Handle counting here later
            dealOne(dealer);
    }
    DEBUG_PRINT("\n");
}

int Game::dealOne(Hand &h) {
    int card = shoe.draw(h);
    DEBUG_PRINT("Dealt " + std::to_string(card) + " ");
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
    //Repeat for each split hand
    for (int i = 0; i < p.numHands(); i++) {
        Player &current = p.getHand(i);
        //Only do this for undetermined results, i.e., don't change LOSS or BLACKJACK
        if (current.won == PUSH) {
            if (dealer.bust() || current.getSum() > dealer.getSum())
                current.won = WIN;
            else if (current.getSum() < dealer.getSum())
                current.won = LOSS;
        }
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