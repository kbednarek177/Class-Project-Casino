#pragma once
#include "igame.hpp"
#include <vector>

class SlotMachine : public IGame {
    private:
        int jackpot; 
        int activeMachines;

        std::vector<char> draws;

        static constexpr int num_of_sym = 5;
        static inline char symbols[] = {'@', '#', '7', '$', '&'};

    public:
        SlotMachine();
        ~SlotMachine() override = default;

        void start(Player& player) override;
        void calculateWinnings(Player& player) override;
        void endRound() override;
        std::string getName() const override { return "Slot Machine"; };

        void spinSymbols();
};