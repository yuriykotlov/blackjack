#include "player.hpp"
#include "dealer.hpp"
#include "display.hpp"
#include "common_vars.hpp"

#include <iostream>

int main(){
    std::cout << R"(
        Welcome to blackjack!
    
    [s] Start game      [q] Exit
    )" << '\n';

    char option{};

    while(true){
        std::cin >> option;

        if (std::cin.eof()){ return 1; }

        if(option != 's' && option != 'q'){
            std::cout << "\nYou didn't enter a valid option, try again.\n";
        } else { break; }
    }

    if(option == 'q') return 0;

    Player player{};

    Dealer &dealer = Dealer::get_dealer();

    dealer.add_player(&player);
    dealer.start_game();
    
    std::cout << Display::game_round(player, dealer.get_hand()) << '\n';

    // if the dealers first card (which is face up) is an ace,
    // the player can choose the insurance option
    player.play_option(dealer.get_hand()[0]->type == CardType::ACE);

    return 0;
}