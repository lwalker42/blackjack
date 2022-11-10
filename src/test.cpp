#include <iostream>
#include <algorithm> //reverse

#include "game.hpp"
#include "player.hpp"
#include "dealer.hpp"
#include "debug.hpp"

#ifndef DEBUG
#error "DEBUG mode must be enabled for test.cpp"
#endif
int main() {
    Rules rules(10, 500);
    Game game(rules);
    //std::cout << rules.toString() << '\n';
    Shoe &shoe = game.shoe;
    std::vector<int> cards = {9, 9, 11, 10, 2, 2, 10, 10, 9, 9};
    std::reverse(cards.begin(), cards.end());
    shoe.deck.insert(shoe.deck.end(), cards.begin(), cards.end());
    Player p1;
    Player p2;
    Dealer d;
    game.addDealer(d);
    game.addPlayer(p1);
    game.addPlayer(p2);
    game.playRound();

    return 0;
}