#pragma once
#include <vector>

#include "rules.hpp"
#include "shoe.hpp"
#include "player.hpp"
#include "dealer.hpp"

class Game {
    Shoe shoe;
    Dealer dealer;
    std::vector<Player> players;

    result playHand(Player &);
    int playDealer();
    void deal();
    int dealOne(Hand &);
    void bet();
    bool checkBlackjack();
    bool checkInsurance();
    result setResult(Player &);
    void cleanupRound(bool, bool);

public:
    Rules rules;
    bool betting;

    Game(Rules &, bool = false);
    void playRound();
    
    
    void addPlayer(const Player &);
    void addDealer(const Dealer &);
};
