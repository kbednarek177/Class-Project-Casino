#pragma once
#include "igame.hpp"
#include "deckofcards.hpp"
#include "ui_manager.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <string>

class CardGame : public IGame {
    protected:
        Deck deck;
        Dealer dealer;

    public:
        CardGame(Dealer d) : dealer(d) {};
        virtual ~CardGame() = default;

        void start(Player& player) override final {
            UI::clearScreen();
            UI::casino_sign();
            std::cout << "============== " << getName() << " ==============\n\n";

            int bet = player.placeBet();
            if (bet <= 0) {
                std::cout << "\nBet cancelled. Going back to menu.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                endRound();
                return;
            }

            prepareDeck();
            playRound(player);        
            calculateWinnings(player);  
            player.resetBet();
            endRound();
        }

        virtual void prepareDeck() {
            deck = Deck();
            deck.shuffle();
        }

        virtual void playRound(Player& player) = 0;
        virtual void calculateWinnings(Player& player) override = 0; 

        virtual void endRound() override {
            UI::pressEnter();
        }
        
        virtual std::string getName() const override = 0;
};