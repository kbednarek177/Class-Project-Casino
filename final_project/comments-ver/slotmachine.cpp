/**
 * @file slotmachine.cpp
 * @brief Implementacja metod dla klasy SlotMachine.
 */
#include "slotmachine.hpp"
#include "ui_manager.hpp"
#include <thread>
#include <random>

SlotMachine::SlotMachine() : jackpot(0) {}

void SlotMachine::start(Player& player){
    UI::clearScreen();
    UI::casino_sign();

    std::cout << "============= SLOT MACHINE =============\n\n";
    std::cout << "========== CURRENT JACKPOT: " << jackpot << " ==========\n\n";

    std::cout << "How many machines do you want to play simultaneously? (1-3): ";
    while (!UI::getValidIntInput(activeMachines) || activeMachines < 1 || activeMachines > 3) {
        std::cout << "Invalid choice! Pick a number between 1 and 3: ";
    }

    std::cout << "\nRemember that your total bet will be split across the machines.\n";

    int bet = player.placeBet();

    if (bet <= 0) {
        std::cout << "\nBet cancelled. Going back to menu.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return; 
    }

    spinSymbols();
    calculateWinnings(player);
    player.resetBet();
    endRound();
}

void SlotMachine::spinSymbols() {
    draws.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4);

    for (int i = 0; i < activeMachines; ++i) {
        char draw1 = symbols[dist(gen)];
        char draw2 = symbols[dist(gen)];
        char draw3 = symbols[dist(gen)];
        draws.push_back(draw1);
        draws.push_back(draw2);
        draws.push_back(draw3);

        std::cout << "Machine " << (i + 1) << " spinning...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "[ " << draw1;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << " | " << draw2;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << " | " << draw3 << " ]\n\n";
    }
}

void SlotMachine::calculateWinnings(Player& player) {
    int totalWinnings = player.getBet() % activeMachines;
    int currentBet = player.getBet() / activeMachines;

    for (int i = 0; i < activeMachines; i++) {
        char draw1 = draws[3*i];
        char draw2 = draws[3*i + 1];
        char draw3 = draws[3*i + 2];
        int winnings = 0;

        std::cout << "--- Machine " << (i + 1) << " ---\n";

        if (draw1 == draw2 && draw2 == draw3) {
            if (draw1 == '7') {
                winnings = currentBet * 50 + jackpot;
                jackpot = 0; 
                std::cout << "HUGE JACKPOT!!!\n";
            } else {
                winnings = currentBet * 10;
                std::cout << "BIG WIN!!!\n";
            }
        } 
        else if ((draw1 == '7' && draw2 == '7') || (draw1 == '7' && draw3 == '7') || (draw2 == '7' && draw3 == '7')) {
            winnings = currentBet * 3;
            std::cout << "LUCKY 7s!\n";
        } 
        else if (draw1 == draw2 || draw2 == draw3 || draw1 == draw3) {
            winnings = currentBet;
            std::cout << "PUSH!\n";
        } 
        else {
            std::cout << "Unlucky. Maybe next time!\n";
            jackpot += (currentBet / 5);
        }

        if (winnings > 0) {
            std::cout << "Machine " << (i + 1) << " pays: " << winnings << " chips!\n";
            totalWinnings += winnings;
        }
        std::cout << "\n";
    }

    if (totalWinnings > player.getBet() % activeMachines) {
        std::cout << "========================================\n";
        std::cout << "TOTAL WINNINGS FROM ALL MACHINES: " << totalWinnings << " chips!\n";
        player.addWinnings(totalWinnings);
    } else {
         std::cout << "No wins this time...\n";
    }
}

void SlotMachine::endRound(){
    UI::pressEnter();
}