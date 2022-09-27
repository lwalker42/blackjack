#include <iostream> //cout
#include "blackjack.hpp"
#include <random>


int main() {
    Shoe shoe(6);
    Rules rules(10, 500);
    Game game(rules);
    std::cout << game.rules.toString();
    Player p;
    Dealer d;
    game.addPlayer(p);
    game.addDealer(d);
    return 0;
}
