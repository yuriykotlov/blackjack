#include "deck.hpp"

#include "common.hpp"

#include <iostream>

// Build cards in Deck
Deck::Deck(){
    int suit_count = static_cast<int>(Suit::COUNT);

    total_cards.reserve(CARDS_PER_SUIT * suit_count);
    drawn_cards.reserve(CARDS_PER_SUIT * suit_count);

    // The for-loop starts at 2 because the first card number allowed is 2.
    // `card_number < CARDS_PER_SUIT (13) + 1` is so that static-casting `int card_number`
    // to CardType will give us the non-regular card types.

    for (int suit_index = 0; suit_index < static_cast<int>(Suit::COUNT); ++suit_index){
        for (int card_number = 2; card_number <= CARDS_PER_SUIT + 1; ++card_number){
            CardType type = card_number <= FACE_CARD_VALUE ? CardType::REGULAR : static_cast<CardType>(card_number);

            Card new_card{
                type,
                static_cast<Suit>(suit_index),
                static_cast<char>(
                    [type, card_number](){
                        switch(type){
                            case CardType::ACE: return ACE_DEFAULT_VALUE;
                            case CardType::REGULAR: return card_number;
                            default: return FACE_CARD_VALUE;
                        }
                    }()
                )
            };

            total_cards.push_back(new_card);
        }
    }
}

// Draw a random card
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