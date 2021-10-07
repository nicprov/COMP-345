#include <iostream>
#include "Cards.h"

using namespace std;

int main(){
    // Create a deck of Warzone cards
    Deck deck = Deck();
    cout << deck << endl;

    // Create a hand by drawing cards
    Hand hand = Hand();
    hand.addCard(deck.draw());
    hand.addCard(deck.draw());
    hand.addCard(deck.draw());
    cout << hand;
}