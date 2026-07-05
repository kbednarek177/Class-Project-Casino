/**
 * @file person.cpp
 * @brief Implementacja metod klasy Player z pliku person.hpp.
 */
#include "person.hpp"
#include "ui_manager.hpp"
#include <iostream>
#include <limits>

int Player::placeBet() {
    if (balance < 50) {
        std::cout << "[!] You do not have enough chips to play. Minimal bet is 50.\n";
        return 0;
    }
    
    bet = 0;
    bool isValid = false;

    while (!isValid) {
        std::cout << "\n========================================\n";
        std::cout << "Your balance: " << balance << " chips\n";
        std::cout << "Place bet (Min: 50, Max: 10 000 000) or quit (0): ";

        if (!UI::getValidIntInput(bet)) {
            std::cout << "\nCan't put that number!\n\n";
            continue;
        }
        
        if(bet == 0) {
            return bet;
        }
        else if (bet < 50) {
            std::cout << "\nMinimal bet is 50!\n\n";
        } 
        else if (bet > 10000000) {
            std::cout << "\nMaximal bet is 10 000 000!\n\n";
        } 
        else if (bet > balance) {
            std::cout << "\nYou do not have enough chips!\n\n";
        } 
        else {
            isValid = true;
        }
    }

    balance -= bet;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return bet;
}

void Player::addWinnings(int num){
    if(num > 0){
        balance += num;
        if(balance >= 10000000){
            balance = 10000000;
        }
    }
}

int Dealer::casino_id = 0;