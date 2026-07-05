/**
 * @file war.cpp
 * @brief Implementacja metod dla klasy War.
 */
#include "war.hpp" 
#include "ui_manager.hpp"

War::War(Dealer dealer) : CardGame(dealer) {}

void War::playRound(Player& player) {
    playerCards.clear();
    dealerCards.clear();
    mainBet = 0;
    sideBetBadBeat = 0;
    sideBetEvenOdd = 0;

    int totalBet = player.getBet(); 

    std::cout << "How many battles do you want to play for this bet? (1-10): ";
    while (!UI::getValidIntInput(numBattles) || numBattles < 1 || numBattles > 10) {
        std::cout << "Invalid choice! Pick a number between 1 and 10: ";
    }

    for (int i = 0; i < numBattles; i++) {
        playerCards.push_back(deck.drawCard());
        dealerCards.push_back(deck.drawCard());
    }

    std::cout << "\n--- DEALER'S CARDS ---\n";
    for (const Card& card : dealerCards) {
        card.print();
    }
    std::cout << "\n--- YOUR CARDS ARE CURRENTLY HIDDEN ---\n";

    std::cout << "\nHow do you want to allocate your bet of " << totalBet << " chips?\n";
    std::cout << "1. All-in on the War (Win pays 2:1)\n";
    std::cout << "2. Half on the War, half on side bets (Bad Beat, Even/Odd)\n";
    std::cout << "Choice: ";

    int choice;
    while (!UI::getValidIntInput(choice) || (choice != 1 && choice != 2)) {
        std::cout << "Invalid choice! Pick 1 or 2: ";
    }

    if (choice == 1) {
        mainBet = totalBet;
        std::cout << "\nAll " << mainBet << " chips have been placed on the War!!\n";
    } else {
        mainBet = totalBet / 2;
        int sidePool = totalBet - mainBet; 
        placeSideBets(sidePool);
    }

    std::cout << "\n--- REVEALING YOUR CARDS ---\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (const Card& card : playerCards) {
        card.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << "\n";
}

void War::placeSideBets(int pool) {
    std::cout << "\n--- PLACING SIDE BETS ---\n";
    std::cout << "You have " << pool << " chips for side bets.\n";
    std::cout << "-> 'The Bad Beat' (An Ace beats a King in any battle) - Pays 10:1\n";
    std::cout << "-> 'Even/Odd' (More odd cards than even cards on the whole board) - Pays 3:1\n\n";
    
    std::cout << "How many chips do you want to place on 'The Bad Beat'?: ";
    while (!UI::getValidIntInput(sideBetBadBeat) || sideBetBadBeat < 0 || sideBetBadBeat > pool) {
        std::cout << "Invalid amount! Enter a number between 0 and " << pool << ": ";
    }
    
    sideBetEvenOdd = pool - sideBetBadBeat;
    std::cout << "Remaining " << sideBetEvenOdd << " chips automatically placed on 'Even/Odd'.\n";
}

void War::resolveSideBets(Player& player) {
    if (sideBetBadBeat == 0 && sideBetEvenOdd == 0) return;
    
    std::cout << "\n--- RESOLVING SIDE BETS ---\n";
    
    if (sideBetBadBeat > 0) {
        bool badBeatOccurred = false;
        for (int i = 0; i < numBattles; ++i) {
            int pVal = int(playerCards[i]);
            int dVal = int(dealerCards[i]);
            if ((pVal == 14 && dVal == 13) || (dVal == 14 && pVal == 13)) {
                badBeatOccurred = true;
                break;
            }
        }
        
        if (badBeatOccurred) {
            std::cout << "[Bad Beat] An Ace beat a King! You win " << sideBetBadBeat * 10 << " chips!\n";
            player.addWinnings(sideBetBadBeat * 10);
        } else {
            std::cout << "[Bad Beat] No Ace beat a King. Bet lost.\n";
        }
    }

    if (sideBetEvenOdd > 0) {
        int oddCount = 0;
        int evenCount = 0;
        
        auto checkOddEven = [&oddCount, &evenCount](const Card& c) {
            int val = int(c); 
            if (val % 2 == 0) { evenCount++; }
            else { oddCount++; }
        };

        for (const Card& c : playerCards) { checkOddEven(c); }
        for (const Card& c : dealerCards) { checkOddEven(c); }

        if (oddCount > evenCount) {
            std::cout << "[Even/Odd] More odd cards (" << oddCount << ") than even (" << evenCount << "). You win " << sideBetEvenOdd * 2 << " chips!\n";
            player.addWinnings( sideBetEvenOdd * 3);
        } else {
            std::cout << "[Even/Odd] Even/Odd bet lost (Odds: " << oddCount << ", Evens: " << evenCount << ").\n";
        }
    }
}

void War::calculateWinnings(Player& player) {
    resolveSideBets(player);

    int playerWins = 0;
    int dealerWins = 0;

    std::cout << "\n--- RESOLVING MAIN BATTLES ---\n";
    for (int i = 0; i < numBattles; ++i) {
        if (playerCards[i] > dealerCards[i]) {
            playerWins++;
        } else if (playerCards[i] < dealerCards[i]) {
            dealerWins++;
        }
    }

    std::cout << "You won " << playerWins << " battles.\n";
    std::cout << "Dealer won " << dealerWins << " battles.\n";

    if (playerWins > dealerWins) {
        std::cout << ">>> YOU WIN THE WAR! <<<\n";
        int winnings = mainBet; 
        player.addWinnings(winnings);
        std::cout << "Main war payout: " << winnings << " chips!\n";
    } 
    else if (playerWins < dealerWins) {
        std::cout << ">>> DEALER WINS THE WAR! You lose your main bet. <<<\n";
    } 
    else {
        std::cout << ">>> WAR IS A TIE! Returning your main bet. <<<\n";
        player.addWinnings(mainBet);
    }
}