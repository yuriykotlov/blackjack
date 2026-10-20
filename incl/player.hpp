#pragma once

#include "common.hpp"

#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cstddef>

class Player{
private:
    Hand hand{};

    int total_cash = PLAYER_STARTING_CASH;
    int current_bet = 0;
    int insurance_bet = 0;

    Options chosen_option = Options::NONE;
    char m_name[MAX_PLAYER_NAME_LEN + 1]{};

public:
    Player(){
        std::string name = onboard();

        size_t target_len = std::min(name.size(), size_t(MAX_PLAYER_NAME_LEN));
        std::copy_n(name.data(), target_len, m_name);

        m_name[MAX_PLAYER_NAME_LEN + 1] = '\0';
    };
    
    // Getters

    Hand &get_hand(){ return hand; }
    std::string get_name() const { return m_name; }
    int get_total_cash() const { return total_cash; }
    int get_current_bet() const { return current_bet; }
    int get_insurance_bet() const { return insurance_bet; }
    Options get_chosen_option() const { return chosen_option; }

    // Setters

    void set_total_cash(int new_cash){ total_cash = new_cash; }
    void set_current_bet(int new_bet){ current_bet = new_bet; }
    void set_insurance_bet(int new_bet){ insurance_bet = new_bet; }
    
    void add_to_total_cash(int extra_cash){ total_cash += extra_cash; }
    void add_to_current_bet(int extra_bet){ current_bet += extra_bet; }

    void give_card(const Card *card){
        hand.push_back(card);
    }

    // Ask the player for their name.
    std::string onboard() const;
    // Ask the player to choose an option to play.
    void play_option(const bool double_down, const bool insurance);
};