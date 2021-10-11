#include <iostream>
#include "Player.h"

using namespace std;

void PlayerDriver(){
    OrderList orderlist = OrderList();
    Hand hand = Hand();
    string territory = "";
    Player p = Player( hand, orderlist);
    Order* deploy = new Deploy(Order::OrderType::deploy);
    p.issueOrder(deploy);
    cout << p;
}