#include <iostream>
#include "Cards.h"

using namespace std;

void cardsDriver(){
    // Create a deck of Warzone cards
    Deck deck = Deck();
    cout << deck << endl;

    // Create a hand by drawing cards
    Hand hand = Hand();
    hand.addCard(deck.draw());
    hand.addCard(deck.draw());
    hand.addCard(deck.draw());
    cout << hand << endl;

    // Call play method on all cards in hand
    for (Card card: hand.getCards()){
        card.play();
        cout << endl;
        hand.removeCard(card);
    }
    cout << hand.getCards().size();

}