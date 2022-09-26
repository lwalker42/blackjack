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

    int playHand(Player &);
    void deal();
    int dealOne(Hand &);
    void bet();
    bool checkBlackjack();
    bool checkInsurance();
    void cleanupRound(bool, bool);

public:
    bool betting;
    Rules rules;

    Game(Rules &, bool = false);
    void playRound();
    
    
    void addPlayer(const Player &);
    void addDealer(const Dealer &);
};
