#include "blackjack.hpp"

Blackjack::Blackjack(Dealer dealer) : CardGame(dealer), playerScore(0), dealerScore(0) {}

int Blackjack::calculateScore(const std::vector<Card>& hand) {
    int score = 0;
    int acesCount = 0;

    for (const Card& card : hand) {
        int value = getBlackjackCardValue(card);
        score += value;
        
        if (value == 11) {
            acesCount++;
        }
    }

    while (score > 21 && acesCount > 0) {
        score -= 10;
        acesCount--;
    }

    return score;
}

void Blackjack::playRound(Player& player) {
    playerHand.clear();
    dealerHand.clear();

    playerHand.push_back(deck.drawCard());
    dealerHand.push_back(deck.drawCard());
    playerHand.push_back(deck.drawCard());
    dealerHand.push_back(deck.drawCard());

    bool playerStands = false;
    bool hasDoubledDown = false;
    Card hiddenCard;

    while (!playerStands) {
        playerScore = calculateScore(playerHand);
        dealerScore = getBlackjackCardValue(dealerHand[0]);

        std::cout << "\n--- DEALER'S HAND: " << dealerScore << " ---\n";
        dealerHand[0].print();
        
        std::cout << "\n--- YOUR HAND: " << playerScore << " ---\n";
        for (const Card& card : playerHand) {
            card.print();
        }
        
        if (playerScore > 21) {
            std::cout << "\nBUST!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }

        std::cout << "\n1. Hit (Draw card)\n";
        std::cout << "2. Stand\n";
        if (playerHand.size() == 2 && calculateScore(playerHand) <= 11) {
            std::cout << "3. Double Down\n";
        }
        std::cout << "Choice: ";
        
        int choice;
        if (!UI::getValidIntInput(choice)) {
            continue;
        }

        if (choice == 1) {
            playerHand.push_back(deck.drawCard());
        } 
        else if (choice == 2) {
            playerStands = true;
        } 
        else if (choice == 3 && playerHand.size() == 2) {
            if (player.doubleBet()) {
                std::cout << "\n>>> You doubled your bet to " << player.getBet() << " chips! <<<\n";
                std::cout << ">>> Drawing a face-down card <<<\n";
                
                hiddenCard = deck.drawCard();
                hasDoubledDown = true;
                playerStands = true;
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                std::cout << "\nNot enough chips to Double Down!\n";
            }
        }
        else {
            std::cout << "\nWrong input number!\n";
        }
    }

    std::cout << "\n--- DEALER'S TURN ---\n";

    dealerScore = calculateScore(dealerHand);
    std::cout << "\n--- DEALER'S HAND: " << dealerScore << " ---\n";
    for (const Card& card : dealerHand) {
        card.print();
    }

    while (dealerScore < 17) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        dealerHand.push_back(deck.drawCard());
        dealerScore = calculateScore(dealerHand);
        std::cout << "\n--- DEALER'S HAND: " << dealerScore << " ---\n";
        for (const Card& card : dealerHand) {
            card.print();
        }
    }

    if (hasDoubledDown) {
        std::cout << "\n--- REVEALING YOUR HIDDEN CARD ---\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
        
        hiddenCard.print();
        playerHand.push_back(hiddenCard);
        playerScore = calculateScore(playerHand);
        
        std::cout << "\n--- YOUR FINAL HAND: " << playerScore << " ---\n";
        
        if (playerScore > 21) {
            std::cout << "\nBUST on Double Down!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void Blackjack::calculateWinnings(Player& player) {
    if (player.getBet() <= 0) {
        return; 
    }

    std::cout << "\n===============================\n";
    std::cout << "Your score: " << playerScore << " | Dealer's score: " << dealerScore << "\n";

    if (playerScore > 21) {
        std::cout << ">>> You lose! <<<\n";
    } 
    else if (dealerScore > 21) {
        std::cout << ">>> Dealer busts! You win! <<<\n";
        player.addWinnings(player.getBet() * 2);
    } 
    else if (playerScore > dealerScore) {
        std::cout << ">>> Your score is higher! You win! <<<\n";
        player.addWinnings(player.getBet() * 2);
    } 
    else if (playerScore < dealerScore) {
        std::cout << ">>> Your score is lower! You lose! <<<\n";
    } 
    else {
        std::cout << ">>> Your scores are tied! Push! Returning the bet. <<<\n";
        player.addWinnings(player.getBet());
    }
}

int Blackjack::getBlackjackCardValue(const Card& card) const {
    int val = int(card);
    if(val == 14){
        return 11;
    }
    if(val > 9){
        return 10;
    }
    return val;
}