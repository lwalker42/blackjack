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

std::string Hand::toString() const {
    std::string str = "[";
    for (int card : cards) {
        str += std::to_string(card) + ", ";
    }

    if (cards.size() > 0) {
        str.pop_back();
        str.pop_back();
    }
    str += "]";
    return str;
}

#include <stdexcept>
#include "debug.hpp"
void Hand::setHand(const std::vector<int> &newCards) {
    #ifdef DEBUG
    cards.clear();
    for (int card : newCards) {
        cards.push_back(card);
    }
    #else
        (void)newCards;
        throw std::runtime_error("Debug mode not active");
    #endif
}