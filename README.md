# Blackjack in the CLI with C++

This is a singleplayer blackjack game made in C++. It features standard game rules, where you are asked to place a bet, and after being dealt your first two cards,
you have the option to choose either stand, hit, fold, double down, or insurance after the dealer has dealt you your cards.

The game has a score system. The number you see on your cards is their respective score, and for face cards like the King, Queen, and Jack, they are all 10.
Aces have by default have a score of 11, however if it causes you to lose (being your score is over 21) the Ace's score becomes 1.

## Options

- **Stand** - Keep your current cards that you are holding and finish your turn.
- **Hit** - Take another card, and you are presented with a set of options again, provided you don't bust.
- **Fold** - Forfeit your hand and get refunded 50% of your bet.
- **Double down** - Double your current bet and take one card, and finish your turn.
- **Insurance** - If the dealer has an *Ace*, you can create an insurance bet being half of your main bet. The dealer must get blackjack for your insurance to pay you back if you lose.

## Prerequisites to building

- **C++20 or higher**
- **CMake 3.20+**
- Appropriate **C++ Compiler** like GCC, Clang or MSCV for your C++ version.
- **Git**

## Building

#### Clone the project
```bash
SSH: git clone git@github.com:yuriykotlov/blackjack.git

HTTPS: git clone https://github.com/yuriykotlov/blackjack.git
```

#### Build the project
```bash
cd blackjack
```

## Running