#include <iostream>
#include "../core/Player.h"

int main(){
    auto* orderlist = new OrderList();
    Hand* hand = new Hand();
    auto name = "Jonathan";
    auto* player = new Player(*hand, *orderlist, name);

    std::cout << *player << std::endl;

    Order* deploy = new Deploy(Order::OrderType::deploy, new Player("john"), new Territory(), 0);
    player->issueOrder(deploy);

    std::cout << *player << std::endl;
}