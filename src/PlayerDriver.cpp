#include <iostream>
#include "Player.h"

using namespace std;

void PlayerDriver(){
    auto* orderlist = new OrderList();
    Hand* hand = new Hand();
    auto* name = new std::string("Jonathan");
    auto* player = new Player(*hand, *orderlist, *name);
    cout << *player << endl;

    Order* deploy = new Deploy(Order::OrderType::deploy);
    player->issueOrder(deploy);
    cout << *player << endl;

    cout << "To Attack: " << player->toAttack() << endl;
    cout << "To Defend: " << player->toDefend();
}