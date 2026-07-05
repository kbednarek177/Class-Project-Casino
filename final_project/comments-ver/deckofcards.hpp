/**
 * @file deckofcards.hpp
 * @brief Definicje klas reprezentujących pojedynczą kartę (Card) oraz talię kart (Deck).
 */
#pragma once
#include <string>
#include <vector>

/**
 * @brief Klasa reprezentująca pojedynczą kartę do gry.
 */
class Card {
    private:
        /** @brief Kolor karty (np. Hearts, Spades). */
        std::string suit;
        /** @brief Figura/Wartość karty (np. 2, 10, King). */
        std::string value;

        static constexpr int num_of_suits = 4;
        static constexpr int num_of_values = 13;
        static inline std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        static inline std::string values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

    public:
        /**
         * @brief Konstruktor tworzący kartę o określonym kolorze i wartości.
         * @param s Kolor karty.
         * @param v Wartość karty.
         */
        Card(const std::string& s, const std::string& v);
        
        /**
         * @brief Konstruktor tworzący kartę na podstawie indeksu (0-51).
         * @param idx Indeks karty.
         */
        Card(int idx);
        
        /** @brief Konstruktor domyślny (tworzy 2 Kier). */
        Card();

        /** @brief Pobiera wartość/figurę karty. */
        std::string getValue() const; 
        
        /** @brief Pobiera kolor karty. */
        std::string getSuit() const;
        
        /** @brief Wypisuje informacje o karcie w konsoli. */
        void print() const;

        /** @brief Przeciążony operator rzutowania na int (zwraca moc karty). */
        explicit operator int() const;
        
        /** @brief Przeciążone operatory porównania. */
        bool operator==(const Card& other) const;
        bool operator!=(const Card& other) const;
        bool operator>(const Card& other) const;
        bool operator<(const Card& other) const;
};

/**
 * @brief Klasa reprezentująca talię kart używaną w grach.
 */
class Deck {
    private:
        /** @brief Wektor przechowujący karty w talii. */
        std::vector<Card> cards;
        /** @brief Rozmiar talii (liczba użytych standardowych talii 52-kartowych). */
        int size;
        
        /**
         * @brief Buduje talię na podstawie podanej liczby standardowych talii.
         * @param num Liczba talii 52-kartowych.
         */
        void build(int num);

    public:
        /**
         * @brief Konstruktor tworzący talię złożoną z wielu standardowych talii.
         * @param num Liczba talii.
         */
        Deck(int num);
        
        /** @brief Konstruktor domyślny (jedna talia 52-kartowa). */
        Deck();

        /** @brief Przywraca talię do stanu początkowego (pełnego). */
        void resetDeck();
        
        /** @brief Tasuje karty w talii. */
        void shuffle();
        
        /**
         * @brief Zdejmuje i zwraca kartę z wierzchu talii.
         * @return Obiekt dociągniętej karty.
         */
        Card drawCard();
};