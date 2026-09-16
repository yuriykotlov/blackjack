#pragma once

#include "utils.hpp"

#include <string>
#include <array>
#include <string_view>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>

// Singleton deck
class Deck{
private:
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

    const int CARDS_PER_SUIT = 13;
    const int FACE_CARDS = 3;

    std::vector<Card> total_cards{};
    std::vector<Card> drawn_cards{};

    Deck(){
        // build deck
        total_cards.reserve(52);
        drawn_cards.reserve(52);
        
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
    static Deck &get_deck(){
        static Deck deck{};
        return deck;
    }

    Deck(const Deck&) = delete; // dont allow duplication
    Deck& operator=(const Deck&) = delete; // dont allow reassignment

    std::string_view card_type_to_string(CardType type){
        switch(type){
            case CardType::Jack: return "Jack";
            case CardType::Queen: return "Queen";
            case CardType::King: return "King";
            case CardType::Ace: return "Ace";
            default: return "???";
        }
    }

    Card draw(){
        int random = get_random_int(1, total_cards.size());

        drawn_cards.emplace_back(total_cards[random]);

        // swap the drawn card with the last card in the deck,
        // and then pop back instead of having to do erase
        total_cards[random] = total_cards.back();
        total_cards.pop_back();

        return Card{};
    }

    void display_deck(){
        for(auto &card : total_cards){
            if(card.type == CardType::Regular){
                std::cout << card.number << " of " << SUITS[card.suit_index] << '\n';
            } else{
                std::cout << card_type_to_string(card.type) << " of " << SUITS[card.suit_index] << '\n';
            }
        }
    }

    void return_drawn_cards(){
        for(auto const &card : drawn_cards){
            
        }
    }

    void shuffle(int shuffle_x_times = 1){
        if(total_cards.empty()){
            std::cout << "There are no cards to shuffle in the deck.\n";
            return;
        }
    }
};