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
    const int SHUFFLE_X_CARDS = 16;

    std::vector<Card> total_cards{};
    std::vector<Card> drawn_cards{};

    Deck(){
        // build deck
        total_cards.reserve(CARDS_PER_SUIT * SUITS.size());
        drawn_cards.reserve(CARDS_PER_SUIT * SUITS.size());
        
        int current_suit_index = 0;
        
        for(auto const &suit : SUITS){
            for(int i = 2; i <= CARDS_PER_SUIT; ++i){
                total_cards.push_back(Card{
                    // will cast to face cards type once above 10, as 13 - 3 = 10
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

    const std::string_view card_type_to_string(const CardType type) const {
        switch(type){
            case CardType::Jack: return "Jack";
            case CardType::Queen: return "Queen";
            case CardType::King: return "King";
            case CardType::Ace: return "Ace";
            default: return "???";
        }
    }

    const Card* const draw(){
        if(total_cards.empty()){
            std::cout << "There are no cards in the deck.\n";
            return nullptr;
        }

        int random = get_random_int(1, total_cards.size());

        drawn_cards.emplace_back(total_cards[random]);

        // swap the drawn card with the last card in the deck,
        // and then pop back instead of having to do erase
        std::swap(total_cards[random], total_cards.back());
        total_cards.pop_back();

        return &drawn_cards.back();
    }

    void display_deck() const {
        if(total_cards.empty()){
            std::cout << "There are no cards in the deck.\n";
            return;
        }

        for(auto &card : total_cards){
            if(card.type == CardType::Regular){
                std::cout << card.number << " of " << SUITS[card.suit_index] << '\n';
            } else{
                std::cout << card_type_to_string(card.type) << " of " << SUITS[card.suit_index] << '\n';
            }
        }
    }

    // return drawn cards to the end of the total_cards
    void return_drawn_cards(){
        if(total_cards.empty()){
            std::cout << "There are no cards to return to the deck.\n";
            return;
        }

        total_cards.insert(total_cards.end(), drawn_cards.cbegin(), drawn_cards.cend());
        total_cards.clear();
    }

    void shuffle(const int shuffle_x_times = 1){
        if(total_cards.empty()){
            std::cout << "There are no cards to shuffle in the deck.\n";
            return;
        }

        int total_cards_size = total_cards.size();

        for(int i = 0; i < SHUFFLE_X_CARDS * shuffle_x_times; ++i){
            int random1 = get_random_int(0, total_cards_size);
            int random2 = get_random_int(0, total_cards_size);
            
            if(random1 == random2){
                if(i > 0) --i;
                continue;
            }
            
            std::swap(total_cards[random1], total_cards[random2]);
        }
    }
};