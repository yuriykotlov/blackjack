#pragma once

#include "deck.hpp"
#include "common_vars.hpp"
#include "player.hpp"

#include <vector>

class Dealer{
private:
    Deck* const pDeck;

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

    void deal_cards();
    
    inline void payout_to(Player &player){
        player.set_total_cash(player.get_current_bet() * 2);
        player.set_current_bet(0);
    }

    inline void take_player_bet(Player &player){
        player.set_current_bet(0);
    }

    // type bool to detect if player has busted (hand value > 21)
    bool evaluate_player_hand(Player &player);
    void evaluate_all_hands();

    void add_players(std::vector<Player> &players);
    void get_bets();
};