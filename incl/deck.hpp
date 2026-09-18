#pragma once

#include "utils.hpp"

#include <string>
#include <array>
#include <string_view>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

constexpr std::array<std::string_view, 4> SUITS{
    "Clubs",
    "Diamonds",
    "Hearts",
    "Spades"
};

// type char is fine since not using large numbers
enum class CardType : char {
    Regular = 0,
    King = 11,
    Queen = 12,
    Jack = 13,
    Ace = 14
};

struct Card {
    CardType type;
    int suit_index;
    int number;
};

constexpr int CARDS_PER_SUIT = 13;
constexpr int FACE_CARDS = 3;

// Singleton deck
class Deck{
private:
    Deck() = default;

    std::vector<Card> total_cards{};
    std::vector<Card> drawn_cards{};

public:
    Deck(const Deck&) = delete; // dont allow duplication
    Deck& operator=(const Deck&) = delete; // dont allow reassignment

    inline static Deck &get_deck(){
        static Deck deck{};
        return deck;
    }
    
    const std::string_view card_type_to_string(const CardType type) const;
    const Card* const draw();

    void shuffle();
    void display_deck() const;
    void return_drawn_cards(); // return drawn cards to the end of the total_cards
};