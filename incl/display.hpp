#include "player.hpp"
#include "game.hpp"
#include "common.hpp"

#include <string>
#include <vector>

namespace Display{
    void enable_ansi_codes();
    std::string card_to_string(const Card &card);
    std::string format_hand(const Hand &hand);
    std::string_view suit_to_string(Suit suit);
    std::string game_round(Player &player, const Hand &dealer_hand);
    std::string end_round(Game &game, const int player_bet);
}