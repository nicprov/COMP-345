#include <iostream>
#include "../core/Orders.h"
#include "../core/Cards.h"
#include "../core/Player.h"
#include "../core/Map.h"

int main() {

    // Inintialize the deck for the game
    Deck* deck = new Deck();

    // Inintialize card with their type
    auto* card1 = new Card(Card::CardType::bomb);
    auto* card2 = new Card(Card::CardType::blockade);
    auto* card3 = new Card(Card::CardType::airlift);
    auto* card4 = new Card(Card::CardType::diplomacy);

    // Inintialize order list of player 1
    auto* orderlist1 = new OrderList();
    // Inintialize hand of player 1
    auto* hand1 = new Hand();
    hand1->addCard(card1);
    hand1->addCard(card2);
    hand1->addCard(card3);
    hand1->addCard(card4);
    // Inintialize player 1 with their hand, order list and name
    auto* name1 = "Jonathan";
    auto* player1 = new Player(PlayerStrategy::human, *hand1, *orderlist1, name1);

    // Inintialize order list of player 2
    auto* orderlist2 = new OrderList();
    // Inintialize hand of player 2
    auto* hand2 = new Hand();
    // Inintialize player 2 with their hand, order list and name
    auto* name2 = "Janet";
    auto* player2 = new Player(PlayerStrategy::human, *hand2, *orderlist2, name2);

    auto players = std::vector<Player*>();
    players.push_back(player1);
    players.push_back(player2);

    // Load map to play with
    std::string mapName = "../maps/solar.map";
    auto* map = new Map(mapName);
    auto* mapLoader = new MapLoader(mapName);
    mapLoader->readMap(map);

    std::cout << std::endl;

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

    std::cout << "Player 1 " << *hand1 << std::endl;
    std::cout << "Player 2 " << *hand2 << std::endl;

    // Add all order types
    OrderList orderList = OrderList();
    Order* deploy = new Deploy(player1, terr1_1, 2);
    Order* advance = new Advance(deck, player1, terr1_1, terr2_1, 2);
    Order* bomb = new Bomb(player1, terr2_1);
    Order* blockade = new Blockade(player1, terr1_2, players);
    Order* airlift = new Airlift(player1, terr1_1, terr1_3, 1);
    Order* negotiate = new Negotiate(player1, player2);
    orderList.add(deploy);
    orderList.add(advance);
    orderList.add(bomb);
    orderList.add(blockade);
    orderList.add(airlift);
    orderList.add(negotiate);

    // Show orders
    std::cout << orderList << std::endl;

    // Validate then execute all orders
    std::cout << std::endl;
    deploy->execute();
    std::cout << std::endl;

    std::cout << std::endl;
    advance->execute();
    std::cout << std::endl;

    std::cout << std::endl;
    bomb->execute();
    std::cout << std::endl;

    std::cout << std::endl;
    blockade->execute();
    std::cout << std::endl;

    std::cout << std::endl;
    airlift->execute();
    std::cout << std::endl;

    std::cout << std::endl;
    negotiate->execute();
    std::cout << std::endl << std::endl;

    // Remove order
    orderList.remove(1);

    // Move order
    orderList.move(airlift, 1, 3);

    //Show orderList again after changes
    std::cout << orderList;
}