#include <iostream>
#include "../core/Cards.h"
#include "../core/Map.h"
#include "../core/Player.h"

int main(){
    // Create a deck of Warzone cards
    auto* map = new Map();
    auto* player = new Player("john", PlayerStrategy::human);
    auto* player2 = new Player("harry", PlayerStrategy::human);
    auto* deck = new Deck();
    std::cout << *deck << std::endl;

    // Create a hand by drawing cards
    auto* hand = new Hand();
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    hand->addCard(deck->draw());
    std::cout << *hand << std::endl;

    Order* order = new Negotiate(player, player2);
    // Call play method on all cards in hand
    for (Card* card: hand->getCards()){
        card->play(deck, player, order);
        std::cout << std::endl;
        hand->removeCard(card);
    }
    std::cout << "Hand size after removing all cards: " << hand->getCards().size();
}