#include "Player.h"

//Player methods
Player::~Player()
{
    delete this->name;
    delete this->hand;
}

Player::Player(const std::string &name) {
    this->name = new std::string(name);
    this->hand = new Hand();
    this->orderList = new OrderList();
}

Player::Player(const Hand &hand, const OrderList &orderlist, const std::string &name)
{
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = new std::string(name);
}

Player::Player(const Player &player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = new std::string(*player.name);
}

Player& Player::operator= (const Player &player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = new std::string(*player.name);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Player &player)
{
    return stream << "Player(" << *player.name << "): " << *player.hand << ", " << *player.orderList;
}

void Player::issueOrder(Order* order) {
    this->orderList->add(order);
}

bool Player::operator==(const Player &player) const {
    return *this->name == *player.name && *this->orderList == *player.orderList && *this->hand == *player.hand;
}

/*
std::vector<Territory *>* Player::toDefend() {
    auto* territoriesToDefend = new std::vector<Territory*>;
    return territoriesToDefend;
}

std::vector<Territory *>* Player::toAttack() {
    auto* territoriesToDefend = new std::vector<Territory*>;
    return territoriesToDefend;
}
*/

std::string &Player::getName()
{
    return *this->name;
}

OrderList &Player::getOrderList()
{
    return *this->orderList;
}