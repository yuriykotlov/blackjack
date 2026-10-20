#include "player.hpp"
#include "game.hpp"
#include "common.hpp"

#include <string>
#include <vector>

namespace Display{
    void enable_ansi_codes();
    std::string game_round(Player &player, const Hand &dealer_hand);
    std::string end_round(Game &game, const int player_bet);
}