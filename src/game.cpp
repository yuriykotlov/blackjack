#include "game.hpp"

#include "player.hpp"
#include "dealer.hpp"
#include "display.hpp"
#include "common.hpp"

#include <utility>

const std::pair<Player, Dealer&> Game::init_game(){
    Display::enable_ansi_codes();
    return {Player{}, Dealer::get_dealer()};
}

// reset all vars in Game class
void Game::init_new_round(){
    std::cout << "\033[2J\033[1;1H";
    
    player_bet_placed = 0;
    is_first_turn = true;

    dealer.reset_variables();
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
}

void Game::end_round(){
    std::cout << "\033[2J\033[1;1H";

    int player_score = get_hand_score(player.get_hand());
    int player_bet = player.get_last_bet_placed();

    if(has_player_folded){
        player_bet *= PLAYER_FOLDED_CASH_MULTIPLIER;
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

    bool dealer_has_ace = hand_has_card_type(dealer.get_hand(), CardType::ACE);

    switch(player.play_option(is_first_turn, dealer_has_ace)){
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

            player_bet_placed = player.get_current_bet();
            player.set_total_cash(player.get_total_cash() - player_bet_placed);
            player.set_current_bet(player_bet_placed * 2);

            dealer.evaluate_hands();
            break;

        case Options::INSURANCE:
            // the player bets half of their current bet, and
            // if the dealer has blackjack and they lose, they get payed out insurance * 2 which
            // equals to their original bet amount
            player_bet_placed = player.get_current_bet();
            player.set_total_cash(player.get_total_cash() - (player_bet_placed / 2));
            player.set_current_bet(player_bet_placed + (player_bet_placed / 2));

            // TODO:
            // implement dealer remembering that they took money from the player for insurance,
            // and payout or refund accordingly
            
            dealer.evaluate_hands();
            break;
                
        default: dealer.evaluate_hands();
    }
}