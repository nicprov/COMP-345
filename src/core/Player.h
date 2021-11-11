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
    std::vector<Territory*>* toDefend();
    std::vector<Territory*>* toAttack();
    void issueOrder(Order*);
    std::string& getName();
    OrderList& getOrderList();
    OrderList* getOrders();
    Hand* hand;
    OrderList* orderList;
    bool hasNegotiationWith(Player* enemy);
private:
    std::string* name;
};
