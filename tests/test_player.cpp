#include <gtest/gtest.h>
#include "player.hpp"

#include <string>

TEST(PlayerTest, PlayerInit){
    std::string player_name = "Joe";
    Player player{player_name};
    
    ASSERT_EQ(player.get_name().length(), player_name.length());
}