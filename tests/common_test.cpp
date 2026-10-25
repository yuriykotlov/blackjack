#include <gtest/gtest.h>
#include "common.hpp"

TEST(CommonTest, HelperFunctions){
    Card card1 = {CardType::REGULAR, Suit::CLUBS, 10};
    Card card2 = {CardType::REGULAR, Suit::DIAMONDS, 7};
    Card card3 = {CardType::REGULAR, Suit::SPADES, 2};

    Hand hand_test = {&card1, &card2, &card3};

    EXPECT_EQ(get_hand_score(hand_test), 19);

    EXPECT_TRUE(hand_has_card_type(hand_test, CardType::REGULAR));
    EXPECT_FALSE(hand_has_card_type(hand_test, CardType::ACE));

    Hand hand_other = {&card1};
    int hand_other_score = get_hand_score(hand_other);

    // hand_test should be the hand with the HandStatus of ::WIN
    EXPECT_EQ(get_hand_status(hand_test, hand_other_score), HandStatus::WIN);
}