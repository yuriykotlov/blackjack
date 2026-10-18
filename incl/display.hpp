#include "player.hpp"
#include "deck.hpp"

#include <string>

namespace Display{
    std::string game_round(Player &player, const std::vector<const Card*> &dealer_hand);
    std::string end_round(const bool player_won, const int player_bet_placed);
}