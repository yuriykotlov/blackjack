#include "display.hpp"

#include "common_vars.hpp"

#include <string>
#include <format>

namespace Display{

std::string card_to_string(const Card &card){
    std::string card_string{};

    if(card.type != CardType::REGULAR){
        card_string.append([&card](){
            switch(card.type){
                case CardType::JACK: return "~J";
                case CardType::QUEEN: return "~Q";
                case CardType::KING: return "~K";
                case CardType::ACE: return "~A";
                default: return "?";
            }
        }());
    } else{
        card_string.append(std::to_string(card.number));
        
        // first letter of suit
        card_string.push_back(SUITS[card.suit_index].front());
    }

    return card_string;
}

std::string format_hand(std::vector<const Card*> &hand){
    std::string hand_string{};

    for(const Card* card : hand){
        std::cout << card->number;
        hand_string.append(std::format("{} ", card_to_string(*card)));
    }

    // remove extra space
    hand_string.pop_back();

    return hand_string;
}

std::string game_round(Player &player, std::vector<const Card*> &dealer_hand){
    std::string dealer_hand_formatted{};

    if(dealer_hand.empty()){
        std::cerr << "Dealer hand is empty?\n";
        return{};
    } else {
        dealer_hand_formatted = format_hand(dealer_hand);

        // if starting the game, hide the dealer's second dealt card
        if(dealer_hand.size() == STARTING_HAND_CARD_AMOUNT){
            int last_index = dealer_hand_formatted.size() - 1;
            dealer_hand_formatted[last_index] = '#';
            dealer_hand_formatted[last_index - 1] = '#'; 
        }
    }

    return std::format(R"(
        [    CASH: ${0}        BET PLACED: ${1}    ]

        Dealer Hand:
        {2}

        Your Hand:
        {3}
    )",
        player.get_total_cash(),
        player.get_current_bet(),
        dealer_hand_formatted,
        format_hand(player.get_hand())
    );
}

std::string end_game(Player &player, std::vector<const Card*> &dealer_hand){
    
}

} // namespace Display