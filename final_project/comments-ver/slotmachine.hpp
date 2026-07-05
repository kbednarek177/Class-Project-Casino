/**
 * @file slotmachine.hpp
 * @brief Definicja klasy SlotMachine, reprezentującej jednorękiego bandytę.
 */
#pragma once
#include "igame.hpp"
#include <vector>

/**
 * @brief Klasa gry na automatach (Slot Machine).
 * Dziedziczy po interfejsie IGame. Obsługuje kręcenie bębnami i naliczanie wygranych z uwzględnieniem jackpota.
 */
class SlotMachine : public IGame {
    private:
        /** @brief Aktualna wartość jackpota. */
        int jackpot; 
        /** @brief Liczba maszyn, na których gracz gra jednocześnie. */
        int activeMachines;

        /** @brief Przechowuje wylosowane symbole z bieżącej rundy dla wszystkich maszyn. */
        std::vector<char> draws;

        /** @brief Całkowita liczba unikalnych symboli na maszynie. */
        static constexpr int num_of_sym = 5;
        /** @brief Tablica dostępnych symboli w grze. */
        static inline char symbols[] = {'@', '#', '7', '$', '&'};

    public:
        /**
         * @brief Konstruktor automatu do gry. Inicjalizuje jackpota.
         */
        SlotMachine();
        
        /** @brief Wirtualny destruktor. */
        ~SlotMachine() override = default;

        /**
         * @brief Rozpoczyna grę na maszynach dla danego gracza.
         * @param player Referencja do gracza.
         */
        void start(Player& player) override;
        
        /**
         * @brief Oblicza wygrane na podstawie wylosowanych symboli na aktywnych maszynach.
         * @param player Referencja do gracza.
         */
        void calculateWinnings(Player& player) override;
        
        /**
         * @brief Zakańcza rundę i czeka na reakcję użytkownika.
         */
        void endRound() override;
        
        /**
         * @brief Zwraca nazwę gry.
         * @return Ciąg znaków "Slot Machine".
         */
        std::string getName() const override { return "Slot Machine"; };

        /**
         * @brief Przeprowadza losowanie symboli (kręcenie) na wszystkich aktywnych maszynach.
         */
        void spinSymbols();
};