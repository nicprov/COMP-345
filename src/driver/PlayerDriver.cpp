#include <iostream>
#include "../core/Player.h"

int main(){
    auto* orderlist = new OrderList();  //create OrderList
    Hand* hand = new Hand();            //create hand of cards
    auto name = "Jonathan";             //name of Player
    auto* player = new Player(*hand, *orderlist, name); //create a Player

    std::cout << *player << std::endl;

    //new deploy order
    Order* deploy = new Deploy(Order::OrderType::deploy, new Player("john"), new Territory(), 0);
   //pass deploy in issueOrder()
    player->issueOrder(deploy);

    std::cout << *player << std::endl;
}