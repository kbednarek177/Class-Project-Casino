/**
 * @file war.hpp
 * @brief Definicja klasy War, reprezentującej karcianą grę w wojnę.
 */
#pragma once
#include "cardgame.hpp"
#include <vector>

/**
 * @brief Klasa obsługująca logikę gry w wojnę.
 * Dziedziczy po klasie CardGame. Pozwala na obstawianie zakładów głównych i pobocznych.
 */
class War final : public CardGame {
    private:
        /** @brief Karty wylosowane przez gracza w danej rundzie. */
        std::vector<Card> playerCards;  
        /** @brief Karty wylosowane przez krupiera w danej rundzie. */
        std::vector<Card> dealerCards;   

        /** @brief Liczba bitew do rozegrania w jednej rundzie (od 1 do 10). */
        int numBattles;
        /** @brief Kwota głównego zakładu na wygraną w wojnie. */
        int mainBet;
        /** @brief Kwota zakładu pobocznego "Bad Beat" (As przegrywa z Królem). */
        int sideBetBadBeat;
        /** @brief Kwota zakładu pobocznego "Even/Odd" (Więcej kart nieparzystych niż parzystych). */
        int sideBetEvenOdd;

        /**
         * @brief Pozwala graczowi rozmieścić żetony na zakładach pobocznych.
         * @param availableSideBetPool Pula żetonów przeznaczona na zakłady poboczne.
         */
        void placeSideBets(int availableSideBetPool);
        
        /**
         * @brief Rozlicza zakłady poboczne gracza i ewentualnie dodaje wygrane.
         * @param player Referencja do obiektu gracza.
         */
        void resolveSideBets(Player& player);

    public:
        /**
         * @brief Konstruktor gry w wojnę.
         * @param dealer Obiekt krupiera obsługującego stół.
         */
        War(Dealer dealer);

        /**
         * @brief Rozpoczyna i przeprowadza pojedynczą rundę wojny dla gracza.
         * @param player Referencja do obiektu gracza.
         */
        void playRound(Player& player) override;
        
        /**
         * @brief Oblicza i przypisuje wygrane po zakończeniu rundy.
         * @param player Referencja do obiektu gracza.
         */
        void calculateWinnings(Player& player) override;
        
        /**
         * @brief Zwraca nazwę gry.
         * @return Ciąg znaków "War".
         */
        std::string getName() const override { return "War"; };
};