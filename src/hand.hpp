#pragma once
#include <vector>

class Hand {
protected:
    std::vector<int> cards;
    int sum = 0;

public:
    bool isSoft = false;
    //Draw one card
    virtual bool draw(int);// = 0;     //
    //Clear hand
    virtual void clear();// = 0;

    int getSum();
    bool bust();
};
