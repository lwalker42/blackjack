#include <iostream>

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
    std::cout << rules.toString();
    std::cout << game.shoe.deck.back() << '\n';
    Shoe &shoe = game.shoe;
    shoe.deck.insert(shoe.deck.end(), {6, 11});
    std::cout << game.shoe.deck.back() << '\n';
    //Player p;
    Dealer d;
    game.addDealer(d);
    game.playRound();

    return 0;
}