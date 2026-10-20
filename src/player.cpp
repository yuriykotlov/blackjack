#include "player.hpp"

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <limits>

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

void Player::play_option(const bool double_down, const bool insurance){
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
    
    chosen_option = static_cast<Options>(option);
}