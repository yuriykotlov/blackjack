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

    Hand &get_hand(){ return dealer_hand; }
    
    void payout_to_player(){
        int player_current_cash = player->get_total_cash();
        player->set_total_cash(player_current_cash + (player->get_current_bet() * 2));
        player->set_current_bet(0);
    }
    // Refund the player X percent of their bet, from 0 to 1.
    void refund_player(double percent_refund = 1){
        int player_current_bet = player->get_current_bet();
        int amount_to_refund = player->get_current_bet() * percent_refund;
        player->set_total_cash(player->get_total_cash() + amount_to_refund);
        player->set_current_bet(player_current_bet - amount_to_refund);
    }
    void take_player_bet(){ player->set_current_bet(0); }
    void add_player(Player *new_player){ player = new_player; }

    void deal_to_hand(Hand &hand, unsigned int x_cards);
    void on_player_fold();
    
    void set_finishing_round(const bool state) { has_finished_round = state; }
    const bool is_finishing_round() const { return has_finished_round; }

    void evaluate_hands();
    void reset_variables();
    void start_dealing();
};