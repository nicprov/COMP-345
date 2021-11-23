#include <iostream>
#include "../core/Player.h"

int main(){
    auto* orderlist = new OrderList();  //create OrderList
    auto* hand = new Hand();            //create hand of cards
    auto name = "Jonathan";             //name of Player
    auto* player = new Player(*hand, *orderlist, name); //create a Player
    std::cout << *player << std::endl;
}