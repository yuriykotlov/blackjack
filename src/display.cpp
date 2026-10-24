#include "display.hpp"

#include "common.hpp"
#include "player.hpp"
#include "dealer.hpp"
#include "game.hpp"

#include <string>
#include <format>
#include <utility>

#if _WIN32
#include <windows.h>
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

namespace Display{

void enable_ansi_codes(){
#if _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hConsole, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);
#endif
}

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
        card_string.push_back(suit_to_string(card.suit).front());
    }

    return card_string;
}

std::string format_hand(const Hand &hand){
    std::string hand_string{};

    for(const Card* card : hand){
        hand_string.append(std::format("{} ", card_to_string(*card)));
    }

    // remove extra space
    hand_string.pop_back();

    return hand_string;
}

std::string_view suit_to_string(Suit suit){
    return SUIT_STRINGS.at(static_cast<int>(suit));
}

std::string game_round(Player &player, const Hand &dealer_hand){
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

std::string end_round(Game &game, int player_bet){
    const auto &player_hand = game.get_player().get_hand();
    const auto &dealer_hand = game.get_dealer().get_hand();

    // Return a pair of strings to display in the console according to the player's hand
    //  .first can be: won / lost / drawed
    //  .second can be: recieved / lost / refunded
    const auto status_string = [&]() -> std::pair<std::string, std::string> {
        switch(get_hand_status(player_hand, get_hand_score(dealer_hand))){
            case HandStatus::WIN:
                player_bet *= PLAYER_WIN_CASH_PAYOUT;
                return {"won", "recieved"};
            case HandStatus::LOSE:
                return {"lost", "lost"};
            default:
                return {"drawed", "refunded"};
        }
    }();

    return std::format(R"(
                   You {0}!

               Cash {1}: ${2}

               
        You had a score of {3}, with hand: {4}

        The Dealer scored {5}, with hand: {6}


        [s] Keep playing    [q] Quit
        )",
        status_string.first,
        status_string.second,
        player_bet,
        get_hand_score(player_hand), format_hand(player_hand),
        get_hand_score(dealer_hand), format_hand(dealer_hand)
    );
}

} // namespace Display