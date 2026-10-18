#include "dealer.hpp"

#include "common.hpp"

#include <iostream>
#include <vector>

void Dealer::deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards){
    for(int i = 0; i < x_cards; ++i){
        if(pDeck->get_total_cards().empty()){
            std::cerr << "No cards to deal to player.\n";
            break;
        }
        
        hand.push_back(pDeck->draw());
    }
}

void Dealer::evaluate_hands(){
    int player_score = get_hand_score(player->get_hand());
    int dealer_score = get_hand_score(dealer_hand);

    if(player_score < dealer_score || player_score > MAX_CARD_SCORE_TO_LOSE){
        take_player_bet();
    } else{
        payout_to_player();
    }

    set_finishing_round(true);
}

void Dealer::reset_variables(){
    pDeck->return_drawn_cards();
    pDeck->shuffle();

    player->get_hand().clear();
    player->set_current_bet(0);

    dealer_hand.clear(); // dealer hand

    set_finishing_round(false);
}

void Dealer::start_dealing(){
    deal_to_hand(player->get_hand(), STARTING_HAND_CARD_AMOUNT);
    deal_to_hand(dealer_hand, STARTING_HAND_CARD_AMOUNT);

    player->place_bet();
}