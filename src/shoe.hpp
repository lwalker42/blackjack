#pragma once
#include <vector>
#include <string>

#include "hand.hpp"

#define CARDS_PER_SUIT 13
#define SUITS 4
const int cards[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

class Shoe {
    int numDecks;
    int numCards;
    std::vector<int> deck;
    void shuffle();

public:
    Shoe(int = 6);
    void initDeck();
    int draw(Hand &);
    bool cutCardReached(double);
    std::string toString();
};
