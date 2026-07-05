#pragma once
#include "cardgame.hpp"

class Blackjack final : public CardGame {
    private:
        std::vector<Card> playerHand;
        std::vector<Card> dealerHand;
        int playerScore;
        int dealerScore;

        int calculateScore(const std::vector<Card>& hand);

    public:
        Blackjack(Dealer dealer);

        void playRound(Player& player) override;
        void calculateWinnings(Player& player) override;
        int getBlackjackCardValue(const Card& card) const;
        
        std::string getName() const override { return "Blackjack"; };
};