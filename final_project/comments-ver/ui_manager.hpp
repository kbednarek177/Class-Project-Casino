/**
 * @file ui_manager.hpp
 * @brief Zbiór funkcji pomocniczych do zarządzania interfejsem użytkownika w konsoli.
 */
#pragma once
#include <iostream>
#include <limits>
#include <memory>
#include "person.hpp"

/**
 * @brief Przestrzeń nazw zawierająca funkcje UI.
 */
namespace UI {
    /**
     * @brief Czyści ekran konsoli.
     */
    inline void clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    /**
     * @brief Wyświetla główny szyld kasyna.
     */
    inline void casino_sign() {
        std::cout << "========================================\n";
        std::cout << "                 CASINO                 \n";
        std::cout << "========================================\n\n";
    }

    /**
     * @brief Wyświetla informacje o aktualnie zalogowanym graczu.
     * @param player Wskaźnik na obiekt zalogowanego gracza.
     */
    inline void log_in(std::shared_ptr<Player> player) {
        if (player) {
            std::cout << "--- Logged in as: " << player->getName() 
                      << " | Balance: " << player->getBalance() << " ---\n\n";
        } else {
            std::cout << "--- YOU ARE NOT LOGGED IN! ---\n\n";
        }
    }

    /**
     * @brief Pobiera i waliduje wejście od użytkownika jako liczbę całkowitą.
     * @param input Referencja do zmiennej, w której zapisana zostanie wprowadzona wartość.
     * @return Zwraca true, jeśli wejście jest poprawną liczbą, w przeciwnym razie false.
     */
    inline bool getValidIntInput(int& input) {
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true; 
    }

    /**
     * @brief Zatrzymuje działanie programu do momentu wciśnięcia klawisza ENTER.
     */
    inline void pressEnter(){
        std::cout << "\nPress ENTER key to go back";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}