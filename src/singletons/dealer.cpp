#include "dealer.hpp"

#include <iostream>

void Dealer::deal_cards(){
    if(players.empty()){
        std::cerr << "No players to deal cards to.\n";
        return;
    }

    if(pDeck->get_total_cards().empty()){
        std::cerr << "No players to deal cards to.\n";
        return;
    }

    int total_cards_size = pDeck->get_total_cards().size();

    for(Player &player : players){
        if(total_cards_size <= 0){
            std::cerr << "No more cards to deal to players.\n";
            return;
        }

        player.give_card(pDeck->draw());
    }
}

bool Dealer::evaluate_player_hand(Player &player){
    std::vector<const Card*> player_hand = player.get_hand();

    if(player_hand.empty()){
        return false;
    }

    int amount{ 0 };

    for(const Card* const card : player_hand){
        if(!card) continue;
        amount += card->number;
    }

    return amount > MAX_CARD_SCORE_TO_LOSE;
}

void Dealer::evaluate_all_hands(){
    for(Player &player : players){
        if(evaluate_player_hand(player)){
            payout_to(player);
        } else{
            take_player_bet(player);
        }
    }
}