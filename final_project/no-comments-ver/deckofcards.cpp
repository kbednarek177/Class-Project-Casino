#include "deckofcards.hpp"
#include <stdexcept>
#include <algorithm>
#include <random>
#include <iostream>

Card::Card(const std::string& s, const std::string& v) : suit(s), value(v) {}

Card::Card(int idx) {
    if(idx >= 0 && idx <= 51){
        suit = suits[idx / 13];
        value = values[idx % 13];
    }
    else {
        throw std::invalid_argument("invalid idx for a card");
    }
}

Card::Card() : Card("Hearts", "2") {}

std::string Card::getValue() const {
    return value;
}

std::string Card::getSuit() const {
    return suit;
}

void Card::print() const{
    std::cout << value << " of " << suit << "\n";
}

Card::operator int() const{
    for(int i=0; i<num_of_values; i++){
        if(values[i] == value){
            return i+2;
        }
    }
    throw std::invalid_argument("invalid card");
}

bool Card::operator==(const Card& other) const {
    return int(*this) == int(other);
}

bool Card::operator!=(const Card& other) const {
    return !(*this == other);
}

bool Card::operator>(const Card& other) const {
    return int(*this) > int(other);
}

bool Card::operator<(const Card& other) const {
    return int(*this) < int(other);
}

Deck::Deck(int num) : size(num){
    if(num > 0 && num <= 100){
        build(num);
        size = 52*num;
    }
    else {
        throw std::invalid_argument("invalid size for a deck of cards");
    }
}

Deck::Deck() : Deck(1) {}

void Deck::build(int num) {
    cards.clear();
    cards.reserve(52 * num);

    for (int i = 0; i < 52 * num; i++) {
        cards.push_back(Card(i % 52));
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(cards.begin(), cards.end(), generator);
}

void Deck::resetDeck() {
    build(size / 52);
}

Card Deck::drawCard() {
    if (cards.empty()) {
        throw std::out_of_range("Cannot draw a card from an empty deck");
    }
    
    Card tmp = cards.back();
    cards.pop_back();
    
    return tmp;
}
