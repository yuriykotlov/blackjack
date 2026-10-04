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

    bool ending_round = false;

public:
    Dealer() : pDeck(&Deck::get_deck()){
        std::cout << "hi, " << pDeck->get_total_cards().size();
    };

    Dealer(const Dealer&) = delete; // dont allow duplication
    Dealer& operator=(const Dealer&) = delete; // dont allow reassignment

    inline static Dealer &get_dealer(){
        static Dealer dealer{};
        return dealer;
    }

    inline std::vector<const Card*> &get_hand(){ return dealer_hand; }
    inline bool is_round_ending(){ return ending_round; }
    
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

    void deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards);

    int check_hand_score(std::vector<const Card*> hand);
    void finish_round();

    void reset_game();
    void start_game();
};