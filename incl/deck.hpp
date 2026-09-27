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
    
    inline const std::vector<Card> &get_total_cards() const { return total_cards; }
    inline const std::vector<Card> &get_drawn_cards() const { return drawn_cards; }
    
    const Card* draw();

    void shuffle();
    void return_drawn_cards(); // return drawn cards to the end of the total_cards
};