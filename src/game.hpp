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

    void cleanupRound();

public:
    bool betting;
    Rules rules;

    Game(Rules &, bool = false);
    void playRound();
    
    void deal();
    int dealOne(Hand &);
    void bet();
    void checkBlackjack();

    void addPlayer(const Player &);
    void addDealer(const Dealer &);
};
