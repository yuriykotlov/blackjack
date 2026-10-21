#include <gtest/gtest.h>
#include "deck.hpp"

TEST(DeckTest, CardsCreated){
    Deck& deck = Deck::get_deck();

    // standard deck size is 52
    int target_deck_size = CARDS_PER_SUIT * SUITS.size();
    EXPECT_EQ(target_deck_size, 52);

    auto &total_cards = deck.get_total_cards();
    EXPECT_EQ(total_cards.size(), target_deck_size);
}