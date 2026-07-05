#pragma once
#include <string>
#include "person.hpp"

class IGame {
    public:
        virtual ~IGame() = default;

        virtual void start(Player& player) = 0;
        virtual void calculateWinnings(Player& player) = 0;
        virtual void endRound() = 0;
        virtual std::string getName() const = 0;
};
