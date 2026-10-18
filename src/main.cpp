#include "game.hpp"

#include <iostream>

bool quit_game(){
    char option;

    while(true){
        std::cin >> option;

        if (std::cin.eof()){ return 1; }

        if(option != 's' && option != 'q'){
            std::cout << "\nYou didn't enter a valid option, try again.\n";
        } else { break; }
    }

    return option == 'q';
}



int main(){
    std::cout << R"(
        Welcome to blackjack!
    
    [s] Start game      [q] Exit
    )" << '\n';

    if(quit_game()) return 0;

    // start of game
    Game game{Game::init_game()};

    while (true){
        // reset vars of game class
        game.init_new_round();

        if(game.get_player().get_total_cash() > 0){
            // while loop
            game.play_round();

            // end round, and prompt if player wants to quit or not
            game.end_round();
            if(quit_game()) return 0;

        } else{
            std::cout << "\033[2J\033[1;1H";

            std::cout << R"(
            Unfortunately, you ran out of cash
                 to play Blackjack with...
            
            [s] Start new game      [q] Exit
            )" << '\n';
            
            if(quit_game()) return 0;

            game.get_player().set_total_cash(PLAYER_STARTING_CASH);
        }
    }

    return 0;
}