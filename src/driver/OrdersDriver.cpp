#include <iostream>
#include "../core/Orders.h"

using std::cout;
using std::endl;

int main() {

    Deck* deck = new Deck();

    Card* card1 = new Card(Card::CardType::bomb);
    Card* card2 = new Card(Card::CardType::blockade);
    Card* card3 = new Card(Card::CardType::airlift);
    Card* card4 = new Card(Card::CardType::diplomacy);
    auto* orderlist1 = new OrderList();
    Hand* hand1 = new Hand();
    hand1->addCard(card1);
    hand1->addCard(card2);
    hand1->addCard(card3);
    hand1->addCard(card4);
    auto* name1 = "Jonathan";
    auto* player1 = new Player(*hand1, *orderlist1, name1);

    auto* orderlist2 = new OrderList();
    Hand* hand2 = new Hand();
    auto* name2 = "Janet";
    auto* player2 = new Player(*hand2, *orderlist2, name2);

    string mapName = "../solar.map";
    Map* map = new Map(mapName);
    auto* mapLoader = new MapLoader(mapName);
    mapLoader->readMap(map);

    cout << endl;

    Territory* terr1_1 = map->getTerritory(1);
    Territory* terr1_2 = map->getTerritory(2);
    Territory* terr1_3 = map->getTerritory(10);
    Territory* terr2_1 = map->getTerritory(3);
    Territory* terr2_2 = map->getTerritory(17);

    terr1_1->setOwner(player1);
    terr1_2->setOwner(player1);
    terr1_3->setOwner(player1);

    terr2_1->setOwner(player2);

    terr1_1->addTroops(5);
    terr1_2->addTroops(5);
    terr1_3->addTroops(5);
    terr2_1->addTroops(5);
    terr2_2->addTroops(5);

    cout << "Player 1 " << *hand1 << endl;
    cout << "Player 2 " << *hand2 << endl;

    // Add all order types
    OrderList orderList = OrderList();
    Order* deploy = new Deploy(Order::OrderType::deploy, player1, terr1_1, 2);
    Order* advance = new Advance(Order::OrderType::advance, deck, player1, terr1_1, terr2_1, 2);
    Order* bomb = new Bomb(Order::OrderType::bomb, player1, terr2_1);
    Order* blockade = new Blockade(Order::OrderType::blockade, player1, terr1_2);
    Order* airlift = new Airlift(Order::OrderType::airlift, player1, terr1_1, terr1_3, 1);
    Order* negotiate = new Negotiate(Order::OrderType::negotiate, player1, player2);
    Order* bomb2 = new Bomb(Order::OrderType::bomb, player1, terr2_2);
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
    deploy->execute();
    cout << endl;

    cout << endl;
    advance->execute();
    cout << endl;

    cout << endl;
    bomb->execute();
    cout << endl;

    cout << endl;
    blockade->execute();
    cout << endl;

    cout << endl;
    airlift->execute();
    cout << endl;

    cout << endl;
    negotiate->execute();
    cout << endl << endl;

    // Remove order
    orderList.remove(1);

    // Move order
    orderList.move(airlift, 1, 3);

    //Show orderList again after changes
    cout << orderList;
}