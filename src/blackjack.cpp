#include <iostream> //cout
#include "blackjack.hpp"
#include <random>


int main() {
    /*
    Shoe shoe(6);
    Rules rules(10, 500);
    Game game(rules);
    std::cout << game.rules.toString();
    Player p;
    Dealer d;
    game.addPlayer(p);
    game.addDealer(d);
    **/
    Player p;
    Shoe shoe;
    p.setHand({4, 4});
    int counts[] = {0, 0, 0, 0, 0};
    int trials;
    std::cout << "Enter number of trials: ";
    std::cin >> trials;
    for (int i = 0; i < trials; i++) {
        int a = p.getAction(shoe);
        counts[a]++;
    }
    double chiSquared = 0;
    for (int i = 0; i < 5; i++) {
        std::cout << "Counts of " << i << ": " << counts[i] << "\n";
        chiSquared += (counts[i] - trials/5.) * (counts[i] - trials/5.) / (trials/5.);
    }
    std::cout << "Chi-squared value: " << chiSquared << " with 4 degrees of freedom";
    return 0;
}
