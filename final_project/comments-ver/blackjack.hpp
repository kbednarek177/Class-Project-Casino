/**
 * @file blackjack.hpp
 * @brief Definicja klasy Blackjack implementującej popularną grę karcianą.
 */
#pragma once
#include "cardgame.hpp"

/**
 * @brief Klasa obsługująca zasady i logikę gry w Blackjacka (oczko).
 */
class Blackjack final : public CardGame {
    private:
        /** @brief Karty aktualnie trzymane przez gracza. */
        std::vector<Card> playerHand;
        /** @brief Karty aktualnie trzymane przez krupiera. */
        std::vector<Card> dealerHand;
        /** @brief Obecny wynik punktowy gracza. */
        int playerScore;
        /** @brief Obecny wynik punktowy krupiera. */
        int dealerScore;

        /**
         * @brief Oblicza wartość punktową ręki z uwzględnieniem zasad dobierania asów (1 lub 11).
         * @param hand Wektor kart do przeliczenia.
         * @return Ostateczny wynik punktowy dla podanej ręki.
         */
        int calculateScore(const std::vector<Card>& hand);

    public:
        /**
         * @brief Konstruktor Blackjacka.
         * @param dealer Obiekt krupiera przypisanego do stołu.
         */
        Blackjack(Dealer dealer);

        /**
         * @brief Przeprowadza główną rozgrywkę w Blackjacka dla gracza (dobieranie kart, podwajanie).
         * @param player Referencja do obiektu gracza.
         */
        void playRound(Player& player) override;
        
        /**
         * @brief Sprawdza wynik końcowy i przydziela wygrane żetony według zasad Blackjacka.
         * @param player Referencja do obiektu gracza.
         */
        void calculateWinnings(Player& player) override;
        
        /**
         * @brief Konwertuje pojedynczą kartę na jej wartość punktową obowiązującą w Blackjacku.
         * @param card Obiekt karty do sprawdzenia.
         * @return Wartość punktowa (2-11).
         */
        int getBlackjackCardValue(const Card& card) const;
        
        /**
         * @brief Pobiera nazwę gry.
         * @return Ciąg znaków "Blackjack".
         */
        std::string getName() const override { return "Blackjack"; };
};