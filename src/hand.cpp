#include "hand.hpp"

bool Hand::draw(int c) {
    if (c == 11) {
        isSoft = true;
        if (sum > 11) sum++;
    }
    cards.push_back(c);

    return true;
}
/*
int Hand::sum() {
        int total = 0;
        int aces = 0;
        for (int i : cards) {
            if (i == 11) aces++;
            total += i;
        }
        while (aces > 0 && total > 21) {
            total -= 10;
            aces--;
        }
        return total;
    }
    */