#pragma once

#include "Orders.h"
#include "Cards.h"
#include <vector>
#include <string>
#include "Map.h"

class Player
{
public:

    Player(vector<Territory>, Hand, OrderList, string);
    // Copy constructor
    Player(const Player*);
    // Assignment operator
    Player& operator= (const Player&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Player*);

    bool operator== (const Player&) const;

    std::vector<Territory*> toDefend();          //***REPLACE VOID WITH TERRITORY
    std::vector<Territory*> toAttack();          //***REPLACE VOID WITH TERRITORY
    void issueOrder(Order*);

    vector<Territory*> territory;
    Hand* hand;
    OrderList* orderList;

private:
    std::string name;

};
