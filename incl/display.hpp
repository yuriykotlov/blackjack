#include "player.hpp"
#include "deck.hpp"
#include "game.hpp"

#include <string>
#include <vector>

namespace Display{
    const std::string game_round(Player &player, const std::vector<const Card*> &dealer_hand);
    const std::string end_round(Game &game, const bool player_won, const int player_bet_placed);
}