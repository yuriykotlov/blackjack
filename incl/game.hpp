#pragma once

#include "player.hpp"
#include "dealer.hpp"

#include <utility>

class Game{
private:
    Player player;
    Dealer &dealer;

    bool first_turn = true;
    int player_bet_placed = 0;

    void prompt_player_options(const bool is_first_turn);

public:
    Game(const std::pair<Player, Dealer&> &pair) : player(pair.first), dealer(pair.second){
        dealer.add_player(&player);
    }

    static const std::pair<Player, Dealer&> init_game();
    
    Player &get_player(){ return player; }
    Dealer &get_dealer(){ return dealer; }

    void init_new_round();
    void play_round();
    void end_round();
};