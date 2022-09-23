#include <vector>
#include <algorithm> //shuffle
#include <random> //random_device

#include "shoe.hpp"

Shoe::Shoe(int d) {
    if (d > 0) numDecks = d;
    numCards = numDecks * CARDS_PER_SUIT * SUITS;
    initDeck();
}

void Shoe::initDeck() {
    deck.clear();
    seen.clear();

    for (int i = 0; i < numDecks * SUITS; i++) {
        for (int j = 0; j < CARDS_PER_SUIT; j++) {
            deck.push_back(cards[j]);
        }        
    }
    shuffle();    
}

int Shoe::draw(Hand &hand) {
    int card = deck.back();
    deck.pop_back();
    if (hand.draw(card)) {
        seen.push_back(card);
    }
    return card;
}

void Shoe::shuffle() {
    std::random_device rd;
    std::mt19937_64 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

bool Shoe::cutCardReached(double d) {
    int fullDeck = CARDS_PER_SUIT * SUITS * numDecks;
    return deck.size() <= (1 - d) * fullDeck;
}

std::string Shoe::toString() {
    std::string str;
    std::for_each(deck.begin(), deck.end(), [&str](int i){
        str.append(std::to_string(i) + " ");
    });
    return str;
}