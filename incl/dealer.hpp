#pragma once

#include "deck.hpp"
#include "common_vars.hpp"
#include "player.hpp"

#include <vector>
#include <memory>

class Dealer{
private:
    Deck* const pDeck;

    Player *player;
    std::vector<const Card*> hand{};

public:
    Dealer() : pDeck(&Deck::get_deck()){};

    Dealer(const Dealer&) = delete; // dont allow duplication
    Dealer& operator=(const Dealer&) = delete; // dont allow reassignment

    inline static Dealer &get_dealer(){
        static Dealer dealer{};
        return dealer;
    }
    
    inline void payout_to_player(){
        player->set_total_cash(player->get_current_bet() * 2);
        player->set_current_bet(0);
    }

    inline void take_player_bet(){
        player->set_current_bet(0);
    }

    inline void add_player(Player *new_player){
        player = new_player;
    }

    void give_new_hand(unsigned int x_cards = 1);
    void deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards);

    // detect if player has busted (hand value > 21)
    void evaluate_player_hand();
};