#pragma once

#include <vector>
#include <string>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

class Territory;

#include "Map.h"

class Player
{
public:
 //   Player(const Hand &hand, const OrderList &orderlist, const string &name, const Map &territoriesList);

    ~Player();
    Player(const std::string&);
    Player(const Hand&, const OrderList&, const std::string&, const Map&);
    // Copy constructor
    Player(const Player&);
    // Assignment operator
    Player& operator= (const Player&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Player&);
    bool operator== (const Player&) const;
    std::vector<Territory*> toDefend();
    std::vector<Territory*> toAttack();
    void issueOrder(Order*);
    std::string& getName();
    OrderList& getOrderList();
    Hand* hand;
    OrderList* orderList;
    //std::vector<Territory*> territoryList;
 //   Territory* territoryList;
    Map* territoriesList;
    int armyPool;
private:
    std::string* name;
};
