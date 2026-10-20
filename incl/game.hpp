#pragma once

#include "player.hpp"
#include "dealer.hpp"

#include <utility>

class Game{
private:
    Player player;
    Dealer &dealer;

    bool is_first_turn = true;
    bool has_player_folded = false;

    void prompt_player_options();
    void reset_state();

public:
    Game(const std::pair<Player, Dealer&> &pair) : player(pair.first), dealer(pair.second){
        dealer.add_player(&player);
        
        is_first_turn = true;
        dealer.reset_variables();

        player.set_total_cash(PLAYER_STARTING_CASH);
        player.set_current_bet(0);
        player.set_insurance_bet(0);
    }

    std::pair<Player, Dealer&> init_game();
    
    Player &get_player(){ return player; }
    Dealer &get_dealer(){ return dealer; }

    void init_new_round();
    void play_round();
    void end_round();
};