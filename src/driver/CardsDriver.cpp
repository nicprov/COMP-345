#include <iostream>
#include "../core/Cards.h"

int main(){
    // Create a deck of Warzone cards
    auto* map = new Map();
    auto* player = new Player("john");
    auto* deck = new Deck();
    std::cout << *deck << std::endl;

    // Create a hand by drawing cards
    auto* hand = new Hand();
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    std::cout << *hand << std::endl;

    auto* orderList = new OrderList();

    // Call play method on all cards in hand
    for (Card* card: hand->getCards()){
        card->play(orderList, hand, deck, player, map, std::vector<Player*>());
        std::cout << std::endl;
        hand->removeCard(card);
    }
    std::cout << "Hand size after removing all cards: " << hand->getCards().size();
}