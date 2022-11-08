#pragma once
#include <vector>
#include <string>

class Hand {
protected:
    std::vector<int> cards;
    int sum = 0;
    bool soft = false;

public:
    //Draw one card
    virtual bool draw(int);
    //Clear hand
    virtual void clear();

    int getSum();
    int size();
    bool isSoft();
    bool bust();

    std::string toString() const;

    //Testing
    void setHand(const std::vector<int> &);
};
