#include "casino.hpp"
#include "profilemanager.hpp"
#include "ui_manager.hpp"
#include <thread>

Casino::Casino() {
    availableGames.clear();
}

void Casino::openCasino() {
    bool isOpen = true;
    std::string errorMessage = ""; 
    int num_of_games;
    std::shared_ptr<Player> currentPlayer = nullptr;

    ProfileManager& manager = ProfileManager::getInstance();

    while (isOpen) {
        num_of_games = static_cast<int>(availableGames.size());
        manager.savePlayers();
        
        UI::clearScreen();
        UI::casino_sign();
        UI::log_in(currentPlayer);

        if (!errorMessage.empty()) {
            std::cout << "[!] " << errorMessage << "\n\n";
            errorMessage = "";
        }

        std::cout << "0. Exit Casino\n";
        std::cout << "1. Create a Player profile\n";
        std::cout << "2. Log in\n";
        std::cout << "3. Log out\n";
        std::cout << "4. Delete a profile\n";
        std::cout << "5. Show players\n";
        std::cout << "OR\n";
        std::cout << "\nAvailable games:\n";

        for (int i = 6; i <= num_of_games + 5; i++) {
            std::cout << i << ". " << availableGames[i-6]->getName() << "\n";
        }
        
        std::cout << "\nChoose your game: ";
        int choice;
        
        if (!UI::getValidIntInput(choice)) {
            errorMessage = "Can't pick that number!";
            continue; 
        }

        if (choice == 0) {
            std::cout << "Leaving the casino. See you next time!\n";
            isOpen = false;
        }
        else if (choice == 1) {
            manager.createProfile();
        }
        else if (choice == 2) {
            if (!(currentPlayer == nullptr)) {
                errorMessage = "You are logged in!";
                continue;
            }
            int id;
            std::cout << "Enter player ID: ";
            if (!UI::getValidIntInput(id)) {
                errorMessage = "Invalid ID";
                continue;
            }
            
            currentPlayer = manager.loginPlayer(id);
            if (currentPlayer == nullptr) {
                errorMessage = "Player not found / Wrong password!";
            }
        }
        else if (choice == 3) {
            currentPlayer = nullptr;
            std::cout << "Logged out.\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if (choice == 4) { 
            int id;
            std::cout << "Enter player ID to delete: ";
            if (!UI::getValidIntInput(id)) {
                errorMessage = "Invalid ID";
                continue;
            }
            
            if (!manager.deleteProfile(id, currentPlayer)) {
                errorMessage = "Deletion failed.";
            } else {
                std::cout << "Profile deleted.\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if (choice == 5) {
            manager.showPlayers();
        }
        else if (choice > 5 && choice <= num_of_games + 5) {
            if (currentPlayer == nullptr) {
                errorMessage = "You must log in to play games!";
            } else {
                availableGames[choice - 6]->start(*currentPlayer);
            }
        }
        else {
            errorMessage = "Can't pick that number!";
        }
    }
}

void Casino::addGame(std::shared_ptr<IGame> game) {
    int tmp = static_cast<int>(availableGames.size());
    for(int i = 0; i < tmp; i++){
        if(game == availableGames[i]){
            return;
        }
    }
    availableGames.push_back(game);
}