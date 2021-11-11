#include <iostream>
#include "../core/Player.h"

using namespace std;

void PlayerDriver(){
    auto* orderlist = new OrderList();
    Hand* hand = new Hand();
    auto* name = new std::string("Jonathan");
    int* army = new int(10);
    auto* player = new Player(*hand, *orderlist, *name, *army);
    cout << *player << endl;

    Order* deploy = new Deploy(Order::OrderType::deploy);
    player->issueOrder(deploy);
    cout << *player << endl;

    cout << "To Attack: " << player->toAttack();
    cout << endl;
    cout << "To Defend: " << player->toDefend();
}