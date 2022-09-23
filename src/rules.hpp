#pragma once

#include <string>

struct Rules {
    int minBet;
    int maxBet;
    bool s17 = true;
    double blackjackPayout = 1.5;
    double deckPenetration = .75;
    int maxHands = 4;
    bool doubleDown = true;
    bool splitUnlikeTens = true;    //Need to change card system to implement this when false
    bool DAS = true;
    bool resplitAces = false;
    bool insurance = true;
    bool lateSurrender = true;
    bool dealerShowHoleCard = true;

    Rules(int minB, int maxB) {
        if (minB >= 0 && minB <= maxB) {
            minBet = minB;
            maxBet = maxB;
        } else {
            throw "Invalid bet sizes";
        }
    };

private:
    //static constexpr const auto toStr = [](auto x) -> std::string {return std::to_string(x) + "\n";};
    template <typename T>
    static std::string toStr(T x) {
        return std::to_string(x) + "\n";
    }
    static std::string toStr(bool x) {
        return (x ? "true" : "false") + std::string("\n");
    }
public:

    std::string toString() {
        std::string str;
        str += "Minimum Bet: " + toStr(minBet);
        str += "Maximum Bet: " + toStr(maxBet);
        str += "Stand 17: " + toStr(s17);
        str += "Blackjack Payout: " + (blackjackPayout == 1.5 ? "3:2\n"
                                        : blackjackPayout == 1.2 ? "6:5\n"
                                        : toStr(blackjackPayout));
        str += "Deck Penetration: " + toStr(deckPenetration);
        str += "Max Hands: " + toStr(maxHands);
        str += "Double Down: " + toStr(doubleDown);
        str += "Split Unlike 10s: " + toStr(splitUnlikeTens);
        str += "DAS: " + toStr(DAS);
        str += "Resplit Aces: " + toStr(resplitAces);
        str += "Insurance: " + toStr(insurance);
        str += "Late Surrender: " + toStr(lateSurrender);
        str += "Dealer Shows Hole Card: " + toStr(dealerShowHoleCard);
        return str;
    }
};
