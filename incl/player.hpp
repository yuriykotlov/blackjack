#pragma once

#include "common_vars.hpp"

#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

class Player{
private:
    std::vector<Card> cards{};

    char m_name[MAX_PLAYER_NAME_LEN + 1]{};
    int id{ -1 };

    int current_bet{ 0 };
    int total_cash{ 500 };

    inline static int total_ids_count{ 0 };

public:
    Player(std::string_view name){
        ++total_ids_count;

        id += total_ids_count;

        size_t target_len = std::min(name.size(), size_t(MAX_PLAYER_NAME_LEN));
        std::copy_n(name.data(), target_len, m_name);

        m_name[MAX_PLAYER_NAME_LEN] = '\0';
    };
    Player onboard(const std::vector<const std::string*> &current_players);

    int bet();

    // dealer_hand is used to see if the dealer has an ace for the insurance option.
    Options play_option(std::vector<Card> &dealer_hand);
};