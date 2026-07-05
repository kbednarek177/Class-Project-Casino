/**
 * @file igame.hpp
 * @brief Definicja interfejsu dla wszystkich gier w kasynie.
 */
#pragma once
#include <string>
#include "person.hpp"

/**
 * @brief Czysto wirtualna klasa bazowa (interfejs) reprezentująca grę w kasynie.
 * Narzuca implementację podstawowych etapów gry: startu, rozliczenia i zakończenia.
 */
class IGame {
    public:
        /** @brief Wirtualny destruktor. */
        virtual ~IGame() = default;

        /**
         * @brief Rozpoczyna grę dla określonego gracza.
         * @param player Referencja do obiektu gracza.
         */
        virtual void start(Player& player) = 0;
        
        /**
         * @brief Rozlicza wygrane i przegrane po zakończonej rundzie.
         * @param player Referencja do obiektu gracza.
         */
        virtual void calculateWinnings(Player& player) = 0;
        
        /**
         * @brief Wykonuje akcje kończące rundę (np. czyszczenie ekranu, powrót do menu).
         */
        virtual void endRound() = 0;
        
        /**
         * @brief Pobiera nazwę gry.
         * @return Zwraca nazwę gry jako ciąg znaków.
         */
        virtual std::string getName() const = 0;
};