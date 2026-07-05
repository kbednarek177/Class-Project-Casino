#pragma once
#include "cardgame.hpp"
#include <vector>

class War final : public CardGame {
    private:
        std::vector<Card> playerCards;  
        std::vector<Card> dealerCards;   

        int numBattles;
        int mainBet;
        int sideBetBadBeat;
        int sideBetEvenOdd;

        void placeSideBets(int availableSideBetPool);
        void resolveSideBets(Player& player);

    public:
        War(Dealer dealer);

        void playRound(Player& player) override;
        void calculateWinnings(Player& player) override;
        
        std::string getName() const override { return "War"; };
};