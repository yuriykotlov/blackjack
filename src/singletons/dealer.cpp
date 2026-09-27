#include "dealer.hpp"

#include <iostream>
#include <vector>
#include <cstddef>

void Dealer::deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards){
    for(std::size_t i = x_cards; i != 0; --i){
        if(pDeck->get_total_cards().empty()){
            std::cerr << "No cards to deal to player.\n";
            break;
        }
        
        hand.push_back(pDeck->draw());
    }
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

void Dealer::reset_game(){
    // clear terminal
    std::cout << "\033[2J\033[1;1H";

    player->get_hand().clear();
    player->set_current_bet(0);
    player->set_total_cash(PLAYER_STARTING_CASH);

    dealer_hand.clear(); // dealer hand
    pDeck->return_drawn_cards();
    pDeck->shuffle();
}

void Dealer::start_game(){
    //reset_game();

    deal_to_hand(player->get_hand(), STARTING_HAND_CARD_AMOUNT);
    deal_to_hand(dealer_hand, STARTING_HAND_CARD_AMOUNT);

    std::cout << "HANDS SIZE: player " << player->get_hand().size() << '\n';
    std::cout << "HANDS SIZE: dealer " << dealer_hand.size() << '\n';
}