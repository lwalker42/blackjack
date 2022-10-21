#pragma once
#include <vector>

class Hand {
protected:
    std::vector<int> cards;
    int sum = 0;

public:
    bool isSoft = false;
    //Draw one card
    virtual bool draw(int);
    //Clear hand
    virtual void clear();

    int getSum();
    bool bust();
};
