#pragma once

#include "deck.hpp"
#include "common_vars.hpp"
#include "player.hpp"

#include <vector>

class Dealer{
private:
    Deck* const pDeck;

    Player *player;
    std::vector<const Card*> dealer_hand{};

    bool has_finished_round = false;

public:
    Dealer() : pDeck(&Deck::get_deck()){
        std::cout << "hi, " << pDeck->get_total_cards().size();
    };

    Dealer(const Dealer&) = delete; // dont allow duplication
    Dealer& operator=(const Dealer&) = delete; // dont allow reassignment

    static Dealer &get_dealer(){
        static Dealer dealer{};
        return dealer;
    }

    std::vector<const Card*> &get_hand(){ return dealer_hand; }
    
    void payout_to_player(){
        player->set_total_cash(player->get_current_bet() * 2);
        player->set_current_bet(0);
    }
    void take_player_bet(){ player->set_current_bet(0); }
    void add_player(Player *new_player){ player = new_player; }

    int check_hand_score(std::vector<const Card*> hand);
    void deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards);
    
    void set_finishing_round(const bool state) { has_finished_round = state; }
    const bool is_finishing_round() const { return has_finished_round; }

    void evaluate_hands();
    void reset_variables();
    void start_dealing();
};