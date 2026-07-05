#pragma once
#include <iostream>
#include <limits>
#include <memory>
#include "person.hpp"

namespace UI {
    inline void clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    inline void casino_sign() {
        std::cout << "========================================\n";
        std::cout << "                 CASINO                 \n";
        std::cout << "========================================\n\n";
    }

    inline void log_in(std::shared_ptr<Player> player) {
        if (player) {
            std::cout << "--- Logged in as: " << player->getName() 
                      << " | Balance: " << player->getBalance() << " ---\n\n";
        } else {
            std::cout << "--- YOU ARE NOT LOGGED IN! ---\n\n";
        }
    }

    inline bool getValidIntInput(int& input) {
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true; 
    }

    inline void pressEnter(){
        std::cout << "\nPress ENTER key to go back";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}