#include <string_view>
#include <array>

// GAME VARIABLES:

constexpr int MAX_PLAYERS{ 4 };
constexpr int MAX_PLAYER_NAME_LEN{ 10 };

constexpr int MAX_TURN_TIME_SEC{ 20 };
constexpr int X_CARDS_DEALT_PER_TURN{ 2 };

// DECK AND CARD RELATED VARIABLES:

constexpr std::array<std::string_view, 4> SUITS{
    "Clubs",
    "Diamonds",
    "Hearts",
    "Spades"
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
    int suit_index{};
    int number{};
};

constexpr int CARDS_PER_SUIT{ 13 };
constexpr int FACE_CARDS{ 3 };