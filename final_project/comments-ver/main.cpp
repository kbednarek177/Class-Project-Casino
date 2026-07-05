/**
 * @file main.cpp
 * @brief Punkt wejścia aplikacji kasyna.
 */
#include "blackjack.hpp"
#include "casino.hpp"
#include "slotmachine.hpp"
#include "person.hpp"
#include "war.hpp"
#include <memory>

using namespace std;

/**
 * @brief Główna funkcja programu, inicjalizuje krupierów, maszyny i otwiera kasyno.
 * @return Zwraca 0 po prawidłowym zakończeniu.
 */
int main(){
    Dealer dealer1 = Dealer("A", "B", 35);
    Dealer dealer2 = Dealer("C", "D", 42);

    shared_ptr<SlotMachine> slotmachine = make_shared<SlotMachine>();
    shared_ptr<Blackjack> blackjack = make_shared<Blackjack>(dealer1);
    shared_ptr<War> war = make_shared<War>(dealer2);

    Casino casino = Casino();
    casino.addGame(slotmachine);
    casino.addGame(blackjack);
    casino.addGame(war);

    casino.openCasino();
}

//  g++ main.cpp blackjack.cpp casino.cpp deckofcards.cpp person.cpp 
//  profilemanager.cpp slotmachine.cpp war.cpp -o casino -Wall -std=c++23