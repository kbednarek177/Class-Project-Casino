#pragma once
#include <string>
#include <vector>

class Card {
    private:
        std::string suit;
        std::string value;

        static constexpr int num_of_suits = 4;
        static constexpr int num_of_values = 13;
        static inline std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        static inline std::string values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

    public:
        Card(const std::string& s, const std::string& v);
        Card(int idx);
        Card();

        std::string getValue() const; 
        std::string getSuit() const;
        void print() const;

        explicit operator int() const;
        bool operator==(const Card& other) const;
        bool operator!=(const Card& other) const;
        bool operator>(const Card& other) const;
        bool operator<(const Card& other) const;
};

class Deck {
    private:
        std::vector<Card> cards;
        int size;
        
        void build(int num);

    public:
        Deck(int num);
        Deck();

        void resetDeck();
        void shuffle();
        Card drawCard();
};

