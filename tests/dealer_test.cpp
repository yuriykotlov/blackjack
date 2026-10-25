#include <gtest/gtest.h>
#include "dealer.hpp"
#include "common.hpp"

Dealer &dealer = Dealer::get_dealer();
Hand hand{};

TEST(DealerTest, Dealing){
    int deal_size = 2;
    dealer.deal_to_hand(hand, deal_size);

    EXPECT_EQ(hand.size(), deal_size);
}