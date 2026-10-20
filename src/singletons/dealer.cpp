#include "dealer.hpp"

#include "common.hpp"

#include <iostream>
#include <vector>
#include <format>
#include <cmath>

void Dealer::deal_to_hand(Hand &hand, unsigned int x_cards){
    for(int i = 0; i < x_cards; ++i){
        if(pDeck->get_total_cards().empty()){
            std::cerr << "No cards to deal to player.\n";
            break;
        }
        
        hand.push_back(pDeck->draw());
    }
}

// Return's true if the dealer want's to keep playing, and false if not.
bool Dealer::decide_to_draw_card(){
    int dealer_score = get_hand_score(dealer_hand);

    // no need to decide if the dealer's score is higher than the player's
    if(has_finished_round){
        if(dealer_score > get_hand_score(player->get_hand())) return false;
    }
    
    if(dealer_score >= MAX_CARD_SCORE){
        return false;
    }

    int current_score = get_hand_score(dealer_hand);

    int min_percent_to_draw = 100;

    if(current_score == MAX_CARD_SCORE - 1){
        min_percent_to_draw = 95;
    } else{
        int percent_of_max_score = (current_score / (MAX_CARD_SCORE * offset_percent)) * 100;
        min_percent_to_draw = std::abs(percent_of_max_score - offset_chance);
    }
    
    if(get_random_int(0, 100) >= min_percent_to_draw){
        deal_to_hand(dealer_hand, 1);
        return true;
    } else{
        return false;
    }
}

void Dealer::on_player_fold(){
    has_player_folded = true;
    refund_player(FOLDED_CHOICE_MULTIPLIER);
    set_finishing_round(true);
}

void Dealer::evaluate_hands(){
    // no need to calculate the dealer's hand status as its inverse of the player's hand status
    int dealer_hand_score = get_hand_score(dealer_hand);

    const HandStatus player_hand_status = get_hand_status(player->get_hand(), get_hand_score(dealer_hand));

    if(player_hand_status == HandStatus::WIN){
        payout_to_player();
    } else if(player_hand_status == HandStatus::DRAW) {
        refund_player();
    } else{ // HandStatus::LOSE
        if(player->get_chosen_option() == Options::INSURANCE && dealer_hand_score == MAX_CARD_SCORE){
            player->add_to_total_cash(player->get_insurance_bet() * PLAYER_INSURANCE_PAYOUT);
        } else{
            player->set_insurance_bet(0);
        }
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

    ask_for_player_bet();
}

void Dealer::ask_for_player_bet(){
    std::cout << std::format(
        "Your current cash balance is: {0}.\nEnter an amount to bet (0-{0}), rounded to the nearest number.",
        player->get_total_cash()
    ) << "\n -> $";

    int amount = 0;

    while(!(std::cin >> amount) || amount > player->get_total_cash() || amount <= 0){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nYou have entered an invalid amount, please try again:\n -> $";
    }
    
    player->set_current_bet(amount);
    player->add_to_total_cash(-amount);
}