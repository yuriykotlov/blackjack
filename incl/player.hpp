#pragma once

#include "common_vars.hpp"

#include <vector>

class Player{
private:
    std::vector<Card> cards{};
    int bet{ 0 };
    int total_cash{ 0 };

public:
    void bet(bool in_or_out);
    
    void play_option();
};