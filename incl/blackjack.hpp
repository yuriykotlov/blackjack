#pragma once

#include "player.hpp"
#include "common_vars.hpp"

#include <vector>

class Blackjack{
private:
    Blackjack() = default;

    Dealer &dealer{};
    Deck &deck{};

    std::vector<Player> players{};

public:
    Blackjack &new_game(){
        static Blackjack blackjack_game{};
        return blackjack_game;
    }

    void start_game();
    void end_game();
}