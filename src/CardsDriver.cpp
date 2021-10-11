#include <iostream>
#include "Cards.h"

using namespace std;

void cardsDriver(){
    // Create a deck of Warzone cards
    Deck* deck = new Deck();
    cout << deck << endl;

    // Create a hand by drawing cards
    Hand* hand = new Hand();
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    cout << hand << endl;

    OrderList* orderList = new OrderList();

    // Call play method on all cards in hand
    for (Card card: hand->getCards()){
        card.play(orderList, hand, deck);
        cout << endl;
        hand->removeCard(&card);
    }
    cout << "Hand size after removing all cards: " << hand->getCards().size();
}