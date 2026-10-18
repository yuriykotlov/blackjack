#pragma once

#include "deck.hpp"
#include "common.hpp"
#include "player.hpp"

#include <vector>

class Dealer{
private:
    Deck* const pDeck;

    Player *player;
    std::vector<const Card*> dealer_hand{};

    bool has_finished_round = false;

public:
    Dealer() : pDeck(&Deck::get_deck()){}

    Dealer(const Dealer&) = delete; // dont allow duplication
    Dealer& operator=(const Dealer&) = delete; // dont allow reassignment

    static Dealer &get_dealer(){
        static Dealer dealer{};
        return dealer;
    }

    std::vector<const Card*> &get_hand(){ return dealer_hand; }
    
    void payout_to_player(){
        int player_current_cash = player->get_total_cash();
        player->set_total_cash(player_current_cash + (player->get_current_bet() * 2));
        player->set_current_bet(0);
    }
    void take_player_bet(){ player->set_current_bet(0); }
    void add_player(Player *new_player){ player = new_player; }

    void deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards);
    
    void set_finishing_round(const bool state) { has_finished_round = state; }
    const bool is_finishing_round() const { return has_finished_round; }

    void evaluate_hands();
    void reset_variables();
    void start_dealing();
};