#include "player.hpp"
#include "dealer.hpp"
#include "display.hpp"
#include "common_vars.hpp"

#include <iostream>

char continue_option(){
    char option;

    while(true){
        std::cin >> option;

        if (std::cin.eof()){ return 1; }

        if(option != 's' && option != 'q'){
            std::cout << "\nYou didn't enter a valid option, try again.\n";
        } else { break; }
    }

    return option;
}

int main(){
    std::cout << R"(
        Welcome to blackjack!
    
    [s] Start game      [q] Exit
    )" << '\n';

    char option = continue_option();
    if(option == 'q') return 0;

    Player player{};
    Dealer &dealer = Dealer::get_dealer();
    dealer.add_player(&player);

    while (true){

    Options option_chosen{};
    bool first_turn = true;
    int player_bet_placed = 0;

    while(true){
        dealer.start_game();

        bool dealer_has_ace = dealer.get_hand()[0]->type == CardType::ACE;

        std::cout << Display::game_round(player, dealer.get_hand()) << '\n';
        option_chosen = player.play_option(first_turn, dealer_has_ace);

        std::cout << "\n\n\nHI HELLO\n\n\n";

        switch(option_chosen){
            case Options::STAND:
                // end turn
                dealer.finish_round();
                break;

            case Options::HIT:
                dealer.deal_to_hand(player.get_hand(), 1);
                std::cout << "hand score: " << dealer.check_hand_score(player.get_hand()) << '\n';

                if(dealer.check_hand_score(player.get_hand()) >= MAX_CARD_SCORE_TO_LOSE){
                    dealer.finish_round();
                }
                break;

            case Options::FOLD:
                // end turn
                dealer.finish_round();
                break;

            case Options::DOUBLE_DOWN:
                dealer.deal_to_hand(player.get_hand(), 1);

                player_bet_placed = player.get_current_bet();
                player.set_total_cash(player.get_total_cash() - player_bet_placed);
                player.set_current_bet(player_bet_placed * 2);

                dealer.finish_round();
                break;

            case Options::INSURANCE:
                player_bet_placed = player.get_current_bet();
                player.set_total_cash(player.get_total_cash() - (player_bet_placed / 2));
                player.set_current_bet(player_bet_placed + (player_bet_placed / 2));
                
                dealer.finish_round();
                break;
                
            default: dealer.finish_round();
        }

        first_turn = false;

        if(dealer.is_round_ending()) break;
    
    } // while(true) inner

    bool has_player_won{ dealer.check_hand_score(player.get_hand()) <= MAX_CARD_SCORE_TO_LOSE };

    std::cout << Display::end_round(
        has_player_won,
        player.get_last_bet_placed()
    ) << '\n';

    // continue game?
    option = continue_option();
    if(option == 'q') break;

    dealer.reset_game();

    } // while(true) outer

    return 0;
}