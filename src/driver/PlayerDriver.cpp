#include <iostream>
#include "../core/Player.h"
#include "../core/Orders.h"
#include "../core/Cards.h"

int main(){
    auto* orderlist = new OrderList();  //create OrderList
    auto* hand = new Hand();            //create hand of cards
    auto name = "Jonathan";             //name of Player
    auto* player = new Player(PlayerStrategy::StrategyType::human, *hand, *orderlist, name); //create a Player
    std::cout << *player << std::endl;
}