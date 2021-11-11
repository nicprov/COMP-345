#include "Player.h"

//Player methods
Player::~Player()
{
    delete this->name;          //deallocate memory
    name = NULL;                //prevents dangling pointer errors
    delete this->hand;
    hand = NULL;
    delete this->orderList;
    orderList = NULL;
}

/**
 *
 * @param name
 */
Player::Player(const std::string& name) {
    this->name = new std::string(name);
    this->hand = new Hand();
    this->orderList = new OrderList();
    this->armyPool = 0;
}

Player::Player(const Hand& hand, const OrderList& orderlist, const std::string& name)
{
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = new std::string(name);
}

Player::Player(const Player& player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = new std::string(*player.name);
}

Player& Player::operator= (const Player& player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = new std::string(*player.name);
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Player& player)
{
    return stream << "Player(" << *player.name << "): " << *player.hand << ", " << *player.orderList;
}

void Player::issueOrder(Order* order) {
    this->orderList->add(order);
}

bool Player::operator==(const Player& player) const {
    return *this->name == *player.name && *this->orderList == *player.orderList && *this->hand == *player.hand;
}

std::vector<Territory*>* Player::toDefend() {
    auto* territoriesToDefend = new std::vector<Territory*>;
    return territoriesToDefend;
}

std::vector<Territory*>* Player::toAttack() {
    auto* territoriesToDefend = new std::vector<Territory*>;
    return territoriesToDefend;
}

std::string& Player::getName()
{
    return *this->name;
}

OrderList& Player::getOrderList()
{
    return *this->orderList;
}

OrderList* Player::getOrders()
{
    return this->orderList;
}

bool Player::hasNegotiationWith(Player* enemy)
{
    for (int i = 0; i < orderList->getOrders().size(); i++)
    {
        if (orderList->getOrders().at(i)->getOrderType() == 6)
        {
            if (dynamic_cast<Negotiate*>(orderList->getOrders().at(i))->getEnemy() == enemy)
            {
                return true;
            }
        }
    }
    return false;
}
