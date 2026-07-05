#include "profilemanager.hpp"
#include "ui_manager.hpp"
#include "json.hpp"
#include <fstream>
#include <memory>
#include <iostream>
#include <thread>

using json = nlohmann::json;

ProfileManager::ProfileManager(const std::string& name) : file(name) {
    loadPlayers();
}

void ProfileManager::savePlayers() {
    std::ofstream out_save(file);

    if (!out_save.is_open()) {
        std::cerr << "Error: Cannot create save file " << file << "\n";
        return;
    }

    json j_array = json::array();

    for (const std::shared_ptr<Player>& p : activePlayers) {
        json j_player;
        j_player["id"] = p->getId();
        j_player["name"] = p->getName();
        j_player["surname"] = p->getSurname();
        j_player["age"] = p->getAge();
        j_player["balance"] = p->getBalance();
        j_player["password"] = p->getPassword();

        j_array.push_back(j_player);
    }

    out_save << j_array.dump(4);
    out_save.close();
}

void ProfileManager::loadPlayers() {
    std::ifstream in_save(file);
    activePlayers.clear();

    if (!in_save.is_open()) {
        return; 
    }

    try {
        json j_array;
        in_save >> j_array; 

        for (const auto& item : j_array) {
            int id = item["id"];
            std::string name = item["name"];
            std::string surname = item["surname"];
            int age = item["age"];
            int balance = item["balance"];
            std::string password = item["password"];

            std::shared_ptr<Player> player = std::make_shared<Player>(id, name, surname, age, password, balance, true);
            activePlayers.push_back(player);
        }
    }
    catch (const json::parse_error& tmp) {
        std::cerr << "JSON loading error: " << tmp.what() << "\n";
    }

    in_save.close();
}

void ProfileManager::createProfile() {
    std::string name, surname, password, submit;
    int age;
    
    while (true) {
        std::cout << "Enter new player name: ";
        std::cin >> name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (isAlpha(name)) {
            break; 
        }
        std::cout << "Invalid input! Name must contain only letters.\n";
    }

    while (true) {
        std::cout << "Enter new player surname: ";
        std::cin >> surname;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (isAlpha(surname)) {
            break; 
        }
        std::cout << "Invalid input! Surname must contain only letters.\n";
    }

    std::cout << "Enter new player age: ";
    while (true) {
        if (!UI::getValidIntInput(age)) {
            std::cout << "\nInvalid input! Please enter a number: "; 
        }
        else if (age < 18 || age > 100) {
            std::cout << "\nYou must be between 18 and 100 years old to play. Pick again: ";
        } 
        else {
            break; 
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Set your password: ";
    std::cin >> password;

    int tmp = 1000;
    for (const std::shared_ptr<Player>& p : activePlayers) {
        if (p->getId() >= tmp) {
            tmp = p->getId() + 1;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Are you sure you want ot create a profile (if yes, type 'y', otherwise type anything else): " << name << " " << surname << " " << age << "\n";
    std::cin >> submit;
    if(submit == "y"){
        std::shared_ptr<Player> newPlayer = std::make_shared<Player>(tmp, name, surname, age, password);
        activePlayers.push_back(newPlayer);
        savePlayers();

        std::cout << "Profile created successfully!\n";
    }
    else{
        std::cout << "Profile sign up failed!\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

std::shared_ptr<Player> ProfileManager::loginPlayer(int id) {
    for (const std::shared_ptr<Player>& p : activePlayers) {
        if (p->getId() == id) {
            std::string pass;
            std::cout << "Enter password: ";
            std::cin >> pass;
            
            if (p->isPasswordValid(pass)) {
                std::cout << "Login successful!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return p;
            } else {
                std::cout << "Incorrect password!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return nullptr;
            }
        }
    }
    return nullptr;
}

bool ProfileManager::deleteProfile(int id, std::shared_ptr<Player>& currentPlayer) {
    for (auto iter = activePlayers.begin(); iter != activePlayers.end(); iter++) {
        if ((*iter)->getId() == id) {
            std::string pwd;
            std::cout << "Enter password to confirm deletion: ";
            std::cin >> pwd;
            
            if ((*iter)->isPasswordValid(pwd)) {
                if (currentPlayer == *iter) { 
                    currentPlayer = nullptr; 
                }
                activePlayers.erase(iter);
                savePlayers(); 
                return true;
            } else {
                std::cout << "Incorrect password. Deletion cancelled.\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return false;
            }
        }
    }
    return false;
}

void ProfileManager::showPlayers() const {
    std::cout << "\n--- REGISTERED PLAYERS ---\n";
    if (activePlayers.empty()) {
        std::cout << "No players registered yet.\n";
    } else {
        for (const std::shared_ptr<Player>& p : activePlayers) {
            std::cout << "- ID:" << p->getId() << " - " << p->getName() << " " << p->getSurname() 
                      << " - Balance: " << p->getBalance() << "\n";
        }
    }
    UI::pressEnter();
}