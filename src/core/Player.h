#pragma once

#include <vector>
#include <string>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

class Order;
class OrderList;
class Hand;
class Territory;
class Map;
class Deck;

class Player
{
public:
    ~Player();
    Player(const std::string&);
    Player(const Hand&, const OrderList&, const std::string&);
    // Copy constructor
    Player(const Player&);
    // Assignment operator
    Player& operator= (const Player&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Player&);
    bool operator== (const Player&) const;
    std::vector<Territory*> toDefend(Map&);
    std::vector<Territory*> toAttack(Map&);
    bool issueOrder(Deck*, Map*,std::vector<Player*>*);
    std::string& getName();
    OrderList& getOrderList();
    OrderList* getOrders();
    Hand* hand;
    OrderList* orderList;
    bool hasNegotiationWith(Player* enemy);
    int* armyPool;
private:
    std::string name;
    Order* advance(Map*, Deck*);
};
