<div align="center">

[![Windows](https://github.com/yuriykotlov/blackjack/actions/workflows/windows-build.yaml/badge.svg?branch=main)](https://github.com/yuriykotlov/blackjack/actions/workflows/windows-build.yaml)
[![MacOS](https://github.com/yuriykotlov/blackjack/actions/workflows/macos-build.yaml/badge.svg?branch=main)](https://github.com/yuriykotlov/blackjack/actions/workflows/macos-build.yaml)
[![Linux](https://github.com/yuriykotlov/blackjack/actions/workflows/linux-build.yaml/badge.svg?branch=main)](https://github.com/yuriykotlov/blackjack/actions/workflows/linux-build.yaml)

</div>

# Blackjack in the CLI with C++

This is a singleplayer blackjack game made in C++. It features standard game rules, where you are asked to place a bet, and after being dealt your first two cards,
you have the option to choose either stand, hit, fold, double down, or insurance after the dealer has dealt you your cards.

## Playing

The game has a score system. The number you see on your cards is their respective score, and for face cards like the King, Queen, and Jack, they are all 10.
Aces have by default have a score of 11, however if it causes you to lose (being your score is over 21) the Ace's score becomes 1.

#### [ Card visual formatting ]

Cards are displayed onto the screen like they appear in person, with their number and their suit like (Diamond or Spade), except where the suit is the first inital letter (D or S). Face cards and Aces do not have their suit displayed. Some examples are provided below:

**10D ~K**<br>
-> corresponds to 10 of Diamonds and King.

**2C ~J**<br>
-> corresponds to 2 of Clubs and Jack.

**~A 3H**<br>
-> corresponds to Ace and 3 of Hearts.

#### [ Options ]

After entering your name and placing your inital bet, you are given the following options, some of which are only available depending on your situation:

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

## Building and Running

#### Clone the project
```bash
SSH: git clone git@github.com:yuriykotlov/blackjack.git

HTTPS: git clone https://github.com/yuriykotlov/blackjack.git
```

#### Building the project

```bash
cd blackjack

# Generate blackjack build
cmake -S . -B build -DBUILD_TESTS=OFF
cmake --build build --target blackjack

# Run the executable
./build/blackjack
```

#### Building the `tests` directory

```bash
# GoogleTest is a submodule in this project, so clone it
git submodule update --init --recursive

# Generate blackjack_test build
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build --target blackjack_test

# Run the test executable
ctest --test-dir build --output-on-failure
```