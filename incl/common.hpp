#pragma once

#include <string_view>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

inline std::mt19937 gen( std::random_device{}() );

// Choose a random number from min to max (inclusive)
const inline int get_random_int(int min, int max){
    return std::uniform_int_distribution<int>(min, max)(gen);
}

// GAME VARIABLES:

constexpr int MAX_PLAYERS = 1;
constexpr int MAX_PLAYER_NAME_LEN = 12;
constexpr int PLAYER_STARTING_CASH = 500;

constexpr int PLAYER_INSURANCE_PAYOUT = 2;
constexpr int PLAYER_WIN_CASH_PAYOUT = 2;
constexpr int DOUBLE_DOWN_CHOICE_MULTIPLIER = 2;
constexpr double FOLDED_CHOICE_MULTIPLIER = 0.5;
constexpr double INSURANCE_CHOICE_MULTIPLIER = 0.5;

constexpr int MAX_TURN_TIME_SEC = 20;
constexpr int MAX_CARD_SCORE = 21;

constexpr int X_CARDS_DEALT_PER_TURN = 2;
constexpr int STARTING_HAND_CARD_AMOUNT = 2;

enum class Options : char{
    NONE = 0,
    STAND = 1,
    HIT = 2,
    FOLD = 3,
    DOUBLE_DOWN = 4,
    INSURANCE = 5
};

enum class HandStatus : char{
    WIN,
    DRAW,
    LOSE
};

// DECK AND CARD RELATED VARIABLES:

constexpr int FACE_CARD_VALUE = 10;
constexpr int ACE_DEFAULT_VALUE = 11;
constexpr int ACE_ALTERNATE_VALUE = 1;

constexpr std::array<std::string_view, 4> SUIT_STRINGS{
    "Clubs",
    "Diamonds",
    "Hearts",
    "Spades"
};

enum class Suit : char{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3,
    COUNT
};

// type char is fine since not using large numbers
enum class CardType : char {
    REGULAR = 0,
    KING = 11,
    QUEEN = 12,
    JACK = 13,
    ACE = 14
};

struct Card {
    CardType type{};
    Suit suit{};
    char number{};

    auto operator<=>(const Card&) const = default;
};

using Hand = std::vector<const Card*>;

constexpr int CARDS_PER_SUIT = 13;
constexpr int FACE_CARDS = 3;

//
// Helper Functions
//

constexpr bool hand_has_card_type(const Hand &hand, const CardType card_type, unsigned int card_position = -1){
    if(hand.empty()) return false;

    if(card_position > -1){
        return hand[0]->type == card_type;
    }

    return std::ranges::any_of(hand, [card_type](const Card* const card){
        return card && card->type == card_type;
    });
}

// Calculate the given hand's score from its cards.
constexpr int get_hand_score(const Hand &hand){
    if(hand.empty()) return -1;

    int amount{ 0 };

    for(const Card* const card : hand){
        if(!card) continue;

        if(card->type == CardType::ACE){
            amount += ACE_DEFAULT_VALUE;
        } else if(card->type != CardType::REGULAR){
            amount += FACE_CARD_VALUE;
        } else{
            amount += card->number;
        }
    }

    if(amount > MAX_CARD_SCORE){
        // check if hand has an ace
        const bool has_ace = hand_has_card_type(hand, CardType::ACE);

        // an ace card initially has a value of 11, but if it causes
        // the player to lose, it is set to a value of 1.
        if(has_ace){
            amount -= ACE_DEFAULT_VALUE;
            amount += ACE_ALTERNATE_VALUE;
        }
    }
    
    return amount;
}

// Return a HandStatus by calculating the hand's score and comparing it to the other_score int.
constexpr HandStatus get_hand_status(const Hand &hand, const int other_score){
    if(other_score > MAX_CARD_SCORE) return HandStatus::WIN;

    const int hand_score = get_hand_score(hand);
    
    if(hand_score > other_score && hand_score <= MAX_CARD_SCORE){
        return HandStatus::WIN;
    } else if(hand_score == other_score){
        return HandStatus::DRAW;
    } else{
        return HandStatus::LOSE;
    }
}