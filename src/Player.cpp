#include "Player.h"

//Player methods
Player::Player(const Hand hands, const OrderList orderlist )
{
   // this->territory = new string(territory);
    this->hand = new Hand(hands);
    this->orderList = new OrderList(orderlist);
}

Player::Player(const Player *player)
{
   // this->territory = new string(*player->territory );
    this->hand = new Hand(*player->hand);
    this->orderList = new OrderList(*player->orderList);
}

Player &Player::operator= (const Player &player)
{
    //this->territory = new string(*player.territory );
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    return *this;
}

std::ostream& operator<< (std::ostream &stream, const Player &player) {
    stream << "Player[" << std::endl;
    stream << "Player hand: " << *player.hand << std::endl;
    stream << "Player orderlist: " << *player.orderList << std::endl;
//    stream << "Player territories: " << Player.territories << endl;
    stream << "]";
    return stream;
}

void Player::issueOrder(Order* order) {
    this->orderList->add(order);
}
