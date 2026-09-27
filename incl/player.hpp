#pragma once

#include "common_vars.hpp"

#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cstddef>

class Player{
private:
    std::vector<const Card*> hand{};

    char m_name[MAX_PLAYER_NAME_LEN + 1]{};
    int id{ -1 };

    int current_bet{ 0 };
    int total_cash{ PLAYER_STARTING_CASH };

    inline static int total_ids_count{ 0 };

public:
    Player(){
        ++total_ids_count;

        id += total_ids_count;

        std::string name = onboard();

        size_t target_len = std::min(name.size(), size_t(MAX_PLAYER_NAME_LEN));
        std::copy_n(name.data(), target_len, m_name);

        m_name[MAX_PLAYER_NAME_LEN] = '\0';
    };
    
    inline std::vector<const Card*> &get_hand(){ return hand; }
    inline int get_current_bet() const { return current_bet; }
    inline int get_total_cash() const { return total_cash; }

    inline void set_current_bet(int new_bet){
        current_bet = new_bet;
    }

    inline void set_total_cash(int new_cash){
        total_cash = new_cash;
    }

    inline void give_card(const Card *card){
        hand.push_back(card);
    }

    std::string onboard() const;
    int place_bet();
    Options play_option(bool can_play_insurance);
};