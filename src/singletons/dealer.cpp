#include "dealer.hpp"

#include <iostream>
#include <vector>

void Dealer::deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards){
    for(size_t i = x_cards; i != 0; --i){
        if(pDeck->get_total_cards().empty()){
            std::cerr << "No cards to deal to player.\n";
            break;
        }
        
        hand.push_back(pDeck->draw());
    }
}

void Dealer::give_new_hand(unsigned int x_cards = 1){
    deal_to_hand(hand, x_cards); // dealer hand

    if(!player){
        std::cerr << "No player to deal cards to.\n";
        return;
    }

    deal_to_hand(player->get_hand(), x_cards);
}

void Dealer::evaluate_player_hand(){
    std::vector<const Card*> player_hand = player->get_hand();

    if(player_hand.empty()){
        std::cerr << "Player has no cards in hand.\n";
        return;
    }

    int amount{ 0 };

    for(const Card* const card : player_hand){
        if(!card) continue;
        amount += card->number;
    }

    if(amount > MAX_CARD_SCORE_TO_LOSE){
        take_player_bet();
    } else{
        payout_to_player();
    }
}