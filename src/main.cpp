#include "game.hpp"

#include <iostream>
#include <limits>
#include <string_view>

bool quit_game(std::string_view message = ""){
    if(!message.empty()){
        std::cout << "\033[2J\033[1;1H";
        std::cout << message << '\n';
    } 

    char option;

    while(true){
        std::cin >> option;

        if (std::cin.eof()){ return 1; }

        if(option != 's' && option != 'q'){
            std::cout << "\nYou didn't enter a valid option, try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else { break; }
    }

    return option == 'q';
}

int main(){
    std::string message = R"(
        Welcome to blackjack!
    
    [s] Start game      [q] Exit
    )";

    if(quit_game(message)) return 0;

    // Setup game
    Game game{game.init_game()};

    while (true){
        // reset vars of game class
        game.init_new_round();

        if(game.get_player().get_total_cash() > 0){
            // while loop
            game.play_round();

            // end round, and prompt if player wants to quit or not
            game.end_round();
            if(quit_game()) break;

        } else{
            message = R"(
            Unfortunately, you ran out of cash
                 to play Blackjack with...
            
            [s] Start new game      [q] Exit
            )";
            
            if(quit_game(message)) break;
        }
    }

    return 0;
}