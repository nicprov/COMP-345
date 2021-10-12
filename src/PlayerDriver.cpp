#include <iostream>
#include "Player.h"

using namespace std;

void PlayerDriver(){
    OrderList* orderlist = new OrderList();
    Hand* hand = new Hand();
    string territory = "";
    Player* p = new Player(*hand, *orderlist);
    Order* deploy = new Deploy(Order::OrderType::deploy);
    p->issueOrder(deploy);
    cout << p;
}