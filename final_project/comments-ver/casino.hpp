/**
 * @file casino.hpp
 * @brief Definicja głównej klasy zarządzającej działaniem całego kasyna.
 */
#pragma once
#include <vector>
#include <memory>
#include "igame.hpp"

/**
 * @brief Klasa główna aplikacji. Przechowuje listę gier i zarządza menu użytkownika.
 */
class Casino {
    private: 
        /** @brief Wektor wskaźników do dostępnych gier w kasynie. */
        std::vector<std::shared_ptr<IGame>> availableGames;

    public:
        /** @brief Konstruktor inicjalizujący puste kasyno. */
        Casino();
        
        /** @brief Główna pętla programu - otwiera menu kasyna i obsługuje wejście użytkownika. */
        void openCasino();
        
        /**
         * @brief Dodaje nową grę do zasobów kasyna.
         * @param game Współdzielony wskaźnik na grę dziedziczącą po IGame.
         */
        void addGame(std::shared_ptr<IGame> game);
};