#include <iostream>
#include "../core/Cards.h"

using namespace std;

int main(){
    // Create a deck of Warzone cards
    Map* map = new Map();
    Player* player = new Player("john");
    Deck* deck = new Deck();
    cout << *deck << endl;

    // Create a hand by drawing cards
    Hand* hand = new Hand();
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    cout << *hand << endl;

    auto* orderList = new OrderList();

    // Call play method on all cards in hand
    for (Card* card: hand->getCards()){
        card->play(orderList, hand, deck, player, map, std::vector<Player*>());
        cout << endl;
        hand->removeCard(card);
    }
    cout << "Hand size after removing all cards: " << hand->getCards().size();
}