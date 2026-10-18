#include "player.hpp"

#include <iostream>
#include <vector>
#include <format>
#include <string>

const std::string Player::onboard() const{
    std::string name{};

    while(true){
        std::cout << "\nEnter your name (1-" << MAX_PLAYER_NAME_LEN << " chars):\n-> ";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        std::cout << '\n';

        if(name.empty() || name.length() > MAX_PLAYER_NAME_LEN){
            std::cout << "Your name is not 1-12 characters.\n";
        } else { break; }
    }
    
    return name;
}

const Options Player::play_option(const bool double_down, const bool insurance){
    std::cout << std::format(R"(
        Choose an option to play:

            [1] : STAND
            [2] : HIT
            [3] : FOLD
            {0}
            {1}
    )",
    double_down ? "[4] : DOUBLE DOWN" : "",
    insurance ? "[5] : INSURANCE" : ""
    ) << "\n -> ";
    
    // valid ascii values for nums 1-5 are 49->53
    int option{};

    while(true){
        std::cin >> option;

        if(option < 0 || option > 3 + double_down + insurance){
            std::cout << "\nThe option you entered was not a valid option (1-5).\nChoose an option to play: ";
        } else { break; }
    }

    return static_cast<Options>(option);
}

void Player::place_bet(){
    std::cout << std::format(
        "Your current cash balance is: {0}.\nEnter an amount to bet (0-{0})",
        total_cash 
    ) << "\n -> $";

    int amount{ 0 };

    while(true){
        if(std::cin >> amount){
            if(amount > 0 && amount <= total_cash){
                break;
            }
            std::cout << "\nYou have entered an invalid amount, please try again:\n -> $";
        } else{
            std::cout << "\nYou have entered an invalid amount, please try again:\n -> $";
            std::cin.clear();
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    total_cash -= amount;
    current_bet = amount;
    last_bet_placed = current_bet;
}