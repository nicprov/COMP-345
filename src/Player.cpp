#include "Player.h"

//Player methods
Player::Player( vector<Territory> territory, const Hand hand, const OrderList orderlist, const string name)
{
    this->territory =  std::vector<Territory>;
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = string(name);
}

Player::Player(const Player *player)
{
    this->territory = new Territory(*player->territory );
    this->hand = new Hand(*player->hand);
    this->orderList = new OrderList(*player->orderList);
    this->name =  string(*player->name);
}

Player &Player::operator= (const Player &player)
{
    this->territory = new Territory(*player.territory );
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = string(*player.name);
    return *this;
}

std::ostream& operator<< (std::ostream &stream, const Player *player) {
    stream << "Player[" << std::endl;
    //stream << "Player hand: " << player->hand << std::endl;
    stream << "Player orderlist: " << *player->orderList << std::endl;
    stream << "Player territories: " << *player->territory << endl;
    stream << "]";
    return stream;
}

void Player::issueOrder(Order* order) {
    this->orderList->add(order);
}

std::vector<Territory*> toDefend(){


}
std::vector<Territory*> toAttack(){

}

//Descructor
Hand::~Player()
{
    Player.clear
    for (Player* hand: *this->hand)         //for loop for territory?
    {
        delete ;
    }
    delete hand;
    delete oderlist;

}
