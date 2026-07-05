#pragma once
#include <vector>
#include <memory>
#include "igame.hpp"

class Casino {
    private: 
        std::vector<std::shared_ptr<IGame>> availableGames;

    public:
        Casino();
        
        void openCasino();
        void addGame(std::shared_ptr<IGame> game);
};
