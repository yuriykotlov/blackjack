#include "deck.hpp"

#include "common.hpp"

#include <iostream>

// build deck
Deck::Deck(){
    total_cards.reserve(CARDS_PER_SUIT * SUITS.size());
    drawn_cards.reserve(CARDS_PER_SUIT * SUITS.size());

    char current_suit_index = 0;

    for (auto const &suit : SUITS){
        for (int i = 0; i <= CARDS_PER_SUIT - 1; ++i){
            int card_number = i + 2;
            Card new_card{
                // will cast to face cards type once above 10, as 13 - 3 = 10
                i <= (CARDS_PER_SUIT - 1) - FACE_CARDS ? CardType::REGULAR : static_cast<CardType>(card_number),
                current_suit_index,
                static_cast<char>(card_number)
            };

            total_cards.push_back(new_card);
        }
        current_suit_index += 1;
    }
}

Card* const Deck::draw(){
    int random = get_random_int(0, total_cards.size() - 1);

    drawn_cards.emplace_back(total_cards[random]);

    // swap the drawn card with the last card in the deck,
    // and then pop back instead of having to do erase
    std::swap(total_cards[random], total_cards.back());
    total_cards.pop_back();

    return &drawn_cards.back();
}

void Deck::return_drawn_cards(){
    if (total_cards.empty()){
        std::cout << "There are no cards to return to the deck.\n";
        return;
    }

    total_cards.insert(total_cards.end(), drawn_cards.cbegin(), drawn_cards.cend());
    drawn_cards.clear();
}

void Deck::shuffle(){
    if (total_cards.empty()){
        std::cout << "There are no cards to shuffle in the deck.\n";
        return;
    }

    int total_cards_size = total_cards.size() - 1;

    for (int i = 0; i < total_cards_size; ++i){
        int random1 = get_random_int(0, total_cards_size);
        int random2 = get_random_int(0, total_cards_size);

        if (random1 == random2){
            if (i > 0) --i;
            continue;
        }

        std::swap(total_cards[random1], total_cards[random2]);
    }
}