#pragma once

#include "utils.hpp"

#include <string>
#include <array>
#include <string_view>
#include <cstdint>
#include <cmath>
#include <iostream>

// Singleton deck
class Deck{
private:
    const int CARDS_PER_SUIT = 13;
    const int FACE_CARDS = 3;

    const std::array<std::string_view, 4> SUITS{
        "Clubs",
        "Diamonds",
        "Hearts",
        "Spades"
    };

    enum class CardType : int {
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

    std::vector<Card> total_cards{};
    std::vector<Card> active_cards{};

    Deck(){
        // build deck
        int current_suit_index = 0;
            
        for(auto const &suit : SUITS){
            for(int i = 2; i <= CARDS_PER_SUIT; ++i){
                total_cards.push_back(Card{
                    // will cast to face cards type once above 10; 13 - 3 = 10
                    i <= CARDS_PER_SUIT - FACE_CARDS ? CardType::Regular : static_cast<CardType>(i),
                    current_suit_index,
                    i
                });
            }

            current_suit_index += 1;
        }
    };

public:
    static Deck &new_deck(){
        static Deck deck{};
        return deck;
    }

    Card draw(){
        return Card{};
    }

    void display_deck(){
        for(auto &card : total_cards){
            std::cout << static_cast<int>(card.type) << " " << SUITS[card.suit_index] << " " << card.number << '\n';
        }
    }
};