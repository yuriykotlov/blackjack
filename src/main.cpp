#include "game.hpp"

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

bool quit_game(){
    return continue_option() == 'q';
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

        game.play_round();

        // end round, and prompt if player wants to quit or not
        game.end_round();
        if(quit_game()) return 0;
    }

    return 0;
}