#pragma once

#include "common_vars.hpp"

#include <string>
#include <array>
#include <string_view>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

// Singleton deck
class Deck{
private:
    std::vector<Card> total_cards{};
    std::vector<Card> drawn_cards{};

public:
    Deck();
    
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