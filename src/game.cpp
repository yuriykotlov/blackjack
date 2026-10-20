#include "game.hpp"

#include "player.hpp"
#include "dealer.hpp"
#include "display.hpp"
#include "common.hpp"

#include <utility>

std::pair<Player, Dealer&> Game::init_game(){
    Display::enable_ansi_codes();
    return {Player{}, Dealer::get_dealer()};
}

// reset all vars in Game class
void Game::init_new_round(){
    std::cout << "\033[2J\033[1;1H";
        
    is_first_turn = true;
    dealer.reset_variables();
    player.set_current_bet(0);
    player.set_insurance_bet(0);
}

void Game::play_round(){
    dealer.start_dealing();

    while(true){
        std::cout << "\033[2J\033[1;1H";
        std::cout << Display::game_round(player, dealer.get_hand()) << '\n';

        prompt_player_options();
        is_first_turn = false;

        if(dealer.is_finishing_round()) break;
    }

    while(dealer.decide_to_draw_card());
}

void Game::end_round(){
    std::cout << "\033[2J\033[1;1H";

    int player_score = get_hand_score(player.get_hand());
    int player_bet = player.get_current_bet();

    if(has_player_folded){
        player_bet *= FOLDED_CHOICE_MULTIPLIER;
    }

    // i know theres no draw condition so the player will win even if they draw for now
    bool has_player_won = (player_score <= MAX_CARD_SCORE) && (player_score >= get_hand_score(dealer.get_hand()));

    std::cout << Display::end_round(
        *this,
        player_bet
    ) << '\n';

    dealer.reset_variables();
}

void Game::prompt_player_options(){
    has_player_folded = false;

    bool dealer_has_ace = hand_has_card_type(dealer.get_hand(), CardType::ACE, 0);

    player.play_option(is_first_turn, dealer_has_ace);

    switch(player.get_chosen_option()){
        case Options::STAND:
            // end turn
            dealer.evaluate_hands();
            break;

        case Options::HIT:
            dealer.deal_to_hand(player.get_hand(), 1);

            if(get_hand_score(player.get_hand()) >= MAX_CARD_SCORE){
                dealer.evaluate_hands();
            }
            break;

        case Options::FOLD:
            // end turn
            has_player_folded = true;
            dealer.on_player_fold();
            break;

        case Options::DOUBLE_DOWN:
            dealer.deal_to_hand(player.get_hand(), 1);
            player.add_to_total_cash(-player.get_current_bet());
            player.add_to_current_bet(player.get_current_bet());

            dealer.evaluate_hands();
            break;

        case Options::INSURANCE:
            // the player bets half of their current bet, and
            // if the dealer has blackjack and they lose, they get payed out insurance * 2 which
            // equals to their original bet amount
            player.set_insurance_bet(player.get_current_bet() * INSURANCE_CHOICE_MULTIPLIER);

            player.add_to_total_cash(-player.get_insurance_bet());
            player.add_to_current_bet(player.get_insurance_bet());
            
            dealer.evaluate_hands();
            break;
                
        default: dealer.evaluate_hands();
    }
}