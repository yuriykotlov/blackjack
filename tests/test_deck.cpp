#include <gtest/gtest.h>
#include "deck.hpp"
#include "common.hpp"
#include "display.hpp"

#include <iostream>

Deck& deck = Deck::get_deck();

TEST(DeckTest, DeckInit){
    // standard deck size is 52
    int target_deck_size = CARDS_PER_SUIT * SUIT_STRINGS.size();
    EXPECT_EQ(target_deck_size, 52);

    auto &total_cards = deck.get_total_cards();
    EXPECT_EQ(total_cards.size(), target_deck_size);
}

TEST(DeckTest, HandInit){
    Card card1 = {CardType::REGULAR, Suit::CLUBS, 10};
    Card card2 = {CardType::ACE, Suit::CLUBS, 11};

    Hand hand{&card1, &card2};

    // Check if hand to string is formatting correctly
    ASSERT_EQ(Display::format_hand(hand), std::string{"10C ~A"});
    
    // Check if score is calculated correctly
    ASSERT_EQ(get_hand_score(hand), 21);
}

TEST(DeckTest, DeckCards){
    auto &cards_in_deck = deck.get_total_cards();

    // Checks if shuffling works. Test the
    // front and back cards to be sure, as
    // there's a chance a card isn't shuffled by chance.

    Card &card1 = cards_in_deck.back();
    Card &card3 = cards_in_deck.front();
    
    deck.shuffle();
    cards_in_deck = deck.get_total_cards();

    Card &card2 = cards_in_deck.back();
    Card &card4 = cards_in_deck.front();

    EXPECT_EQ(card1, card2);
    EXPECT_EQ(card3, card4);

    // Drawing card tests
    Card *drawn_card = deck.draw();
    EXPECT_EQ(cards_in_deck.size(), cards_in_deck.capacity() - 1);
    EXPECT_EQ(deck.get_drawn_cards()[0], *drawn_card);

    deck.return_drawn_cards();
    cards_in_deck = deck.get_total_cards();

    // Returning cards to tests
    EXPECT_TRUE(deck.get_drawn_cards().empty());
    EXPECT_EQ(cards_in_deck.size(), cards_in_deck.capacity());
}