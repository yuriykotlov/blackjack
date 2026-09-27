#include "player.hpp"
#include "deck.hpp"

#include <string>

namespace Display{
    std::string game_round(Player &player, std::vector<const Card*> &dealer_hand);
    std::string end_game(Player &player, std::vector<const Card*> &dealer_hand);
}