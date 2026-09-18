#include "deck.hpp"

#include <iostream>

int main(){
    Deck &deck = Deck::get_deck();
    deck.display_deck();

    std::cout << '\n' << "###\n\n";

    deck.shuffle();
    deck.display_deck();
}