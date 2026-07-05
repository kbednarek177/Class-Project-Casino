/**
 * @file cardgame.hpp
 * @brief Definicja bazowej klasy dla wszystkich gier karcianych w kasynie.
 */
#pragma once
#include "igame.hpp"
#include "deckofcards.hpp"
#include "ui_manager.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <string>

/**
 * @brief Abstrakcyjna klasa reprezentująca grę karcianą.
 * Dziedziczy po IGame i zarządza wspólnymi elementami: talią i krupierem.
 */
class CardGame : public IGame {
    protected:
        /** @brief Talia kart używana w grze. */
        Deck deck;
        /** @brief Krupier prowadzący grę. */
        Dealer dealer;

    public:
        /**
         * @brief Konstruktor gry karcianej.
         * @param d Obiekt krupiera.
         */
        CardGame(Dealer d) : dealer(d) {};
        
        /** @brief Wirtualny destruktor. */
        virtual ~CardGame() = default;

        /**
         * @brief Standardowa sekwencja startowa gry karcianej (finalna, nie może być nadpisana).
         * @param player Gracz przystępujący do gry.
         */
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

        /** @brief Przygotowuje talię na nową rundę (resetuje i tasuje). */
        virtual void prepareDeck() {
            deck = Deck();
            deck.shuffle();
        }

        /**
         * @brief Czysto wirtualna metoda przeprowadzająca główną logikę rundy.
         * @param player Gracz uczestniczący w rundzie.
         */
        virtual void playRound(Player& player) = 0;
        
        virtual void calculateWinnings(Player& player) override = 0; 

        /** @brief Obsługuje zakończenie rundy (oczekuje na interakcję gracza). */
        virtual void endRound() override {
            UI::pressEnter();
        }
        
        virtual std::string getName() const override = 0;
};