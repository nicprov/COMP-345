#pragma once

#include "Orders.h"
#include "Cards.h"
#include <vector>
#include <string>


class Player
{
public:

    Player(Hand, OrderList);
    // Copy constructor
    Player(const Player*);
    // Assignment operator
    Player& operator= (const Player&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Player&);

    bool operator== (const Player&) const;

//    std::vector<string> toDefend();                                                    //***REPLACE VOID WITH TERRITORY
 //   std::vector<string> toAttack();                                                    //***REPLACE VOID WITH TERRITORY
    void issueOrder(Order*);

private:
    Hand* hand;
 //   string territory;
    OrderList* orderList;

};
