#include "hand.hpp"

bool Hand::draw(int c) {
    if (c == 11 && sum <= 10) {
        soft = true;
        sum += c;
    } else if (c == 11) {
        sum++;
    } else {
        sum += c;
    }
    if (soft && sum > 21) {
        sum -= 10;
        soft = false;
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

int Hand::size() {
    return cards.size();
}

bool Hand::isSoft() {
    return soft;
}

bool Hand::bust() {
    return sum > 21;
}