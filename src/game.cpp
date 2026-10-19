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
    
    first_turn = true;
    player_bet_placed = 0;

    dealer.reset_variables();
}

void Game::play_round(){
    dealer.start_dealing();

    while(true){
        std::cout << "\033[2J\033[1;1H";
        std::cout << Display::game_round(player, dealer.get_hand()) << '\n';

        prompt_player_options(first_turn);
        first_turn = false;

        if(dealer.is_finishing_round()) break;
    }
}

void Game::end_round(){
    std::cout << "\033[2J\033[1;1H";

    int player_score = get_hand_score(player.get_hand());

    // i know theres no draw condition so the player will win even if they draw for now
    bool has_player_won = (player_score <= MAX_CARD_SCORE) && (player_score >= get_hand_score(dealer.get_hand()));

    std::cout << Display::end_round(
        *this,
        player.get_last_bet_placed()
    ) << '\n';

    dealer.reset_variables();
}

void Game::prompt_player_options(const bool is_first_turn){
    bool dealer_has_ace = dealer.get_hand()[0]->type == CardType::ACE;

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
            dealer.evaluate_hands();
            break;

        case Options::DOUBLE_DOWN:
            dealer.deal_to_hand(player.get_hand(), 1);

            player_bet_placed = player.get_current_bet();
            player.set_total_cash(player.get_total_cash() - player_bet_placed);
            player.set_current_bet(player_bet_placed * 2);

            dealer.evaluate_hands();
            break;

        case Options::INSURANCE:
            player_bet_placed = player.get_current_bet();
            player.set_total_cash(player.get_total_cash() - (player_bet_placed / 2));
            player.set_current_bet(player_bet_placed + (player_bet_placed / 2));
                
            dealer.evaluate_hands();
            break;
                
        default: dealer.evaluate_hands();
    }
}