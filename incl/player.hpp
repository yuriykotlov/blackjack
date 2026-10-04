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

    int current_bet{ 0 };
    int total_cash{ PLAYER_STARTING_CASH };

    int last_bet_placed{ 0 };

public:
    Player(){
        std::string name = onboard();

        size_t target_len = std::min(name.size(), size_t(MAX_PLAYER_NAME_LEN));
        std::copy_n(name.data(), target_len, m_name);

        m_name[MAX_PLAYER_NAME_LEN] = '\0';
    };
    
    inline std::string get_name() const { return m_name; }
    inline std::vector<const Card*> &get_hand(){ return hand; }

    inline int get_current_bet() const { return current_bet; }
    inline int get_total_cash() const { return total_cash; }
    inline int get_last_bet_placed() const { return last_bet_placed; }

    inline void set_current_bet(int new_bet){
        current_bet = new_bet;
        // if its equal to 0 then its being reset, and we don't want that
        if(current_bet != 0) last_bet_placed = current_bet;
    }

    inline void set_total_cash(int new_cash){
        total_cash = new_cash;
    }

    inline void give_card(const Card *card){
        hand.push_back(card);
    }

    std::string onboard() const;
    void place_bet();
    Options play_option(const bool double_down, const bool insurance);
};