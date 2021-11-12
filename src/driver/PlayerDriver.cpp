#include <iostream>
#include "../core/Player.h"

int main(){
    auto* orderlist = new OrderList();
    Hand* hand = new Hand();
    auto name = "Jonathan";
    auto* territories = new vector<Territory*>();
    auto* player = new Player(*hand, *orderlist, name, territories);

    std::cout << *player << std::endl;

    Order* deploy = new Deploy(Order::OrderType::deploy, new Player("john"), new Territory(), 0);
    player->issueOrder(deploy);

    std::cout << *player << std::endl;
}