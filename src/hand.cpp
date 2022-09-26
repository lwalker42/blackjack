#include "hand.hpp"

bool Hand::draw(int c) {
    if (c == 11 && sum <= 10) {
        isSoft = true;
        sum += c;
    } else if (c == 11) {
        sum++;
    } else {
        sum += c;
    }
    if (isSoft && sum > 21) {
        sum -= 10;
        isSoft = false;
    }
    cards.push_back(c);

    return true;
}


void Hand::clear() {
    cards.clear();
    sum = 0;
}

int Hand::getSum() {
    return sum;
}

bool Hand::bust() {
    return sum > 21;
}