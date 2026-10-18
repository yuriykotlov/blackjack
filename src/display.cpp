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

std::string format_hand(const std::vector<const Card*> &hand){
    std::string hand_string{};

    for(const Card* card : hand){
        std::cout << card->number;
        hand_string.append(std::format("{} ", card_to_string(*card)));
    }

    // remove extra space
    hand_string.pop_back();

    return hand_string;
}

std::string game_round(Player &player, const std::vector<const Card*> &dealer_hand){
    std::string dealer_hand_formatted = format_hand(dealer_hand);

    if(dealer_hand.empty()){
        std::cerr << "Dealer hand is empty?\n";
        return{};
        
    } else if(dealer_hand.size() == STARTING_HAND_CARD_AMOUNT){
        for(int i = dealer_hand_formatted.length() - 1; i > 0; --i){
            if(dealer_hand_formatted[i] == ' '){
                dealer_hand_formatted.erase(i + 1);
                dealer_hand_formatted += "[?]";
                break;
            }
        }
    }

    return std::format(R"(
        Player: {0}
        [    CASH: ${1}        BET PLACED: ${2}    ]

        Dealer Hand:
        {3}

        Your Hand:
        {4}
    )",
        player.get_name(),
        player.get_total_cash(),
        player.get_current_bet(),
        dealer_hand_formatted,
        format_hand(player.get_hand())
    );
}

std::string end_round(const bool player_won, const int player_bet_placed){
    return std::format(R"(
                   You {0}!

               Cash {0}: ${1}


        [s] Keep playing    [q] Quit
        )",
        player_won ? "won" : "lost",
        player_bet_placed
    );
}

} // namespace Display