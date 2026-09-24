#pragma once

#include "deck.hpp"
#include "common_vars.hpp"
#include "player.hpp"

#include <vector>

class Dealer{
private:
    Deck *pDeck{ nullptr };

    std::vector<Player> players{};
    std::vector<Card> hand{};

public:
    Dealer() : pDeck(&Deck::get_deck()){};

    Dealer(const Dealer&) = delete; // dont allow duplication
    Dealer& operator=(const Dealer&) = delete; // dont allow reassignment

    inline static Dealer &get_dealer(){
        static Dealer dealer{};
        return dealer;
    }

    void deal_cards(std::vector<Player> &players);
    void recieve_bet(int bet, Player &player_betting);

    void evaluate_all_hands();
    bool evaluate_player_hand(Player &player);
    void payout_to(Player &player);

    void add_players(std::vector<Player> &players);
};