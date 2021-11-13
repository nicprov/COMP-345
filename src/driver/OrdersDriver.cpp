#include <iostream>
#include "../core/Orders.h"

using std::cout;
using std::endl;

<<<<<<< Updated upstream
void ordersDriver() {
=======
int main() {

    // Inintialize the deck for the game
    Deck* deck = new Deck();

    // Inintialize card with their type
    Card* card1 = new Card(Card::CardType::bomb);
    Card* card2 = new Card(Card::CardType::blockade);
    Card* card3 = new Card(Card::CardType::airlift);
    Card* card4 = new Card(Card::CardType::diplomacy);

    // Inintialize order list of player 1
    auto* orderlist1 = new OrderList();
    // Inintialize hand of player 1
    Hand* hand1 = new Hand();
    hand1->addCard(card1);
    hand1->addCard(card2);
    hand1->addCard(card3);
    hand1->addCard(card4);
    // Inintialize player 1 with their hand, order list and name
    auto* name1 = "Jonathan";
    auto* player1 = new Player(*hand1, *orderlist1, name1);

    // Inintialize order list of player 2
    auto* orderlist2 = new OrderList();
    // Inintialize hand of player 2
    Hand* hand2 = new Hand();
    // Inintialize player 2 with their hand, order list and name
    auto* name2 = "Janet";
    auto* player2 = new Player(*hand2, *orderlist2, name2);

    // Load map to play with
    string mapName = "../solar.map";
    Map* map = new Map(mapName);
    auto* mapLoader = new MapLoader(mapName);
    mapLoader->readMap(map);

    cout << endl;

    // Give players some Territories
    Territory* terr1_1 = map->getTerritory(1);
    Territory* terr1_2 = map->getTerritory(2);
    Territory* terr1_3 = map->getTerritory(10);
    Territory* terr2_1 = map->getTerritory(3);
    Territory* terr2_2 = map->getTerritory(17);

    terr1_1->setOwner(player1);
    terr1_2->setOwner(player1);
    terr1_3->setOwner(player1);

    terr2_1->setOwner(player2);

    // Add armies to each player's Territories
    terr1_1->addTroops(5);
    terr1_2->addTroops(5);
    terr1_3->addTroops(5);
    terr2_1->addTroops(5);
    terr2_2->addTroops(5);

    cout << "Player 1 " << *hand1 << endl;
    cout << "Player 2 " << *hand2 << endl;
>>>>>>> Stashed changes

    // Add all order types
    OrderList orderList = OrderList();
    Order* deploy = new Deploy(Order::OrderType::deploy);
    Order* advance = new Advance(Order::OrderType::advance);
    Order* bomb = new Bomb(Order::OrderType::bomb);
    Order* blockade = new Blockade(Order::OrderType::blockade);
    Order* airlift = new Airlift(Order::OrderType::airlift);
    Order* negotiate = new Negotiate(Order::OrderType::negotiate);
    orderList.add(deploy);
    orderList.add(advance);
    orderList.add(bomb);
    orderList.add(blockade);
    orderList.add(airlift);
    orderList.add(negotiate);

    // Show orders
    cout << orderList << endl;

    // Validate then execute all orders
    cout << endl;
    if (deploy->validate())
        deploy->execute();
    cout << endl;
    if (advance->validate())
        advance->execute();
    cout << endl;
    if (bomb->validate())
        bomb->execute();
    cout << endl;
    if (blockade->validate())
        blockade->execute();
    cout << endl;
    if (airlift->validate())
        airlift->execute();
    cout << endl;
    if (negotiate->validate())
        negotiate->execute();
    cout << endl << endl;

    // Remove order
    orderList.remove(1);

    // Move order
    orderList.move(airlift, 1, 3);

    //Show orderList again after changes
    cout << orderList;
}