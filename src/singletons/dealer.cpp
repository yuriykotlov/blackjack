#include "dealer.hpp"

#include "common.hpp"

#include <iostream>
#include <vector>

void Dealer::deal_to_hand(Hand &hand, unsigned int x_cards){
    for(int i = 0; i < x_cards; ++i){
        if(pDeck->get_total_cards().empty()){
            std::cerr << "No cards to deal to player.\n";
            break;
        }
        
        hand.push_back(pDeck->draw());
    }
}

void Dealer::on_player_fold(){
    has_player_folded = true;
    refund_player(PLAYER_FOLDED_CASH_MULTIPLIER);
    set_finishing_round(true);
}

void Dealer::evaluate_hands(){
    // no need to calculate the dealer's hand status as its inverse of the player's hand status
    const HandStatus player_hand_status = get_hand_status(player->get_hand(), get_hand_score(dealer_hand));

    if(player_hand_status == HandStatus::WIN){
        payout_to_player();
    } else if(player_hand_status == HandStatus::DRAW) {
        refund_player();
    } else{
        take_player_bet();
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