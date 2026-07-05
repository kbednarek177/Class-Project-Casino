#pragma once
#include <vector>
#include <memory>
#include <string>
#include "person.hpp" 

class ProfileManager {
    private:
        std::string file;
        std::vector<std::shared_ptr<Player>> activePlayers;

        ProfileManager(const std::string& name = "players.json");

    public:
        ProfileManager(const ProfileManager&) = delete;
        ProfileManager& operator=(const ProfileManager&) = delete;  

        static ProfileManager& getInstance() {
            static ProfileManager instance; 
            return instance;
        }

        void savePlayers();
        void loadPlayers(); 
        
        void createProfile();
        std::shared_ptr<Player> loginPlayer(int id);
        bool deleteProfile(int id, std::shared_ptr<Player>& currentPlayer);
        void showPlayers() const;

        bool isAlpha(const std::string& n){
            if (n.empty()) { return false; }
                for (char c : n) {
                    if (!std::isalpha(static_cast<unsigned char>(c))) {
                        return false; 
                    }
            }
            return true;
        }
};