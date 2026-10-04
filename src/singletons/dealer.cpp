#include "dealer.hpp"

#include <iostream>
#include <vector>

void Dealer::deal_to_hand(std::vector<const Card*> &hand, unsigned int x_cards){
    for(int i = 0; i < x_cards; ++i){
        if(pDeck->get_total_cards().empty()){
            std::cerr << "No cards to deal to player.\n";
            break;
        }
        
        hand.push_back(pDeck->draw());

        std::cout << "DEALT A CARD TO PLAYER\n";
    }
}

int Dealer::check_hand_score(std::vector<const Card*> hand){
    if(hand.empty()){
        std::cerr << "Player has no cards in hand.\n";
        return -1;
    }

    int amount{ 0 };

    for(const Card* const card : hand){
        if(!card) continue;
        amount += card->number;
    }
    
    return amount;
}

void Dealer::finish_round(){
    ending_round = true;

    int player_score = check_hand_score(player->get_hand());
    int dealer_score = check_hand_score(dealer_hand);

    if(player_score < dealer_score || player_score > MAX_CARD_SCORE_TO_LOSE){
        take_player_bet();
    } else{
        payout_to_player();
    }
}

void Dealer::reset_game(){
    // clear terminal
    std::cout << "\033[2J\033[1;1H";
    
    ending_round = false;
    
    pDeck->return_drawn_cards();
    pDeck->shuffle();

    player->get_hand().clear();
    player->set_current_bet(0);
    player->set_total_cash(PLAYER_STARTING_CASH);

    dealer_hand.clear(); // dealer hand
}

void Dealer::start_game(){
    reset_game();

    deal_to_hand(player->get_hand(), STARTING_HAND_CARD_AMOUNT);
    deal_to_hand(dealer_hand, STARTING_HAND_CARD_AMOUNT);

    player->place_bet();
}