#pragma once

#include "deck.hpp"
#include "common.hpp"
#include "player.hpp"

#include <vector>

class Dealer{
private:
    Deck* const pDeck;

    Player *player;
    Hand dealer_hand{};
    
    double offset_percent = 1.5; // for ::decide_to_draw_card
    int offset_chance = 50;      // for ::decide_to_draw_card

    bool has_finished_round = false;
    bool has_player_folded = false;

public:
    Dealer() : pDeck(&Deck::get_deck()){}

    Dealer(const Dealer&) = delete; // dont allow duplication
    Dealer& operator=(const Dealer&) = delete; // dont allow reassignment

    static Dealer &get_dealer(){
        static Dealer dealer{};
        return dealer;
    }
    
    void reset_variables();
    void set_finishing_round(const bool state) { has_finished_round = state; }
    const bool is_finishing_round() const { return has_finished_round; }

    // Hand functions

    Hand &get_hand(){ return dealer_hand; }
    void deal_to_hand(Hand &hand, unsigned int x_cards);
    void evaluate_hands();
    void start_dealing();
    void decide_to_draw_card();

    // Player functions
    
    void add_player(Player *new_player){ player = new_player; }
    void ask_for_player_bet();
    void on_player_fold();
    void take_player_bet(){ player->set_current_bet(0); }
    void payout_to_player(){
        int player_current_cash = player->get_total_cash();
        player->add_to_total_cash(player->get_current_bet() * PLAYER_WIN_CASH_PAYOUT);
        player->set_current_bet(0);
    }
    // Refund the player X percent of their bet, from 0 to 1.
    void refund_player(double percent_refund = 1){
        int amount_to_refund = player->get_current_bet() * percent_refund;
        player->set_current_bet(amount_to_refund);
        player->add_to_total_cash(amount_to_refund);
    }
};