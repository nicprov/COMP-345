#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include <vector>
using namespace  std;

//Player methods
Player::~Player()
{
    delete this->name;          //deallocate memory
    name = nullptr;                //prevents dangling pointer errors
    delete this->hand;
    hand = nullptr;
    delete this->orderList;
    orderList = nullptr;
    delete this->territoriesList;
    orderList = nullptr;
}

/**
 *
 * @param name
 */
Player::Player(const std::string& name) {
    this->name = new std::string(name);
    this->hand = new Hand();
    this->orderList = new OrderList();
    this->territoriesList = new Map();
    this->armyPool = 0;
}

/**
 * Player Constructor
 * @param hand
 * @param orderlist
 * @param name
 */
Player::Player(const Hand &hand, const OrderList &orderlist, const std::string &name, const Map &territoriesList)
{
    this->armyPool = 0;
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = new std::string(name);
    this->territoriesList = new Map(territoriesList);
}

Player::Player(const Player& player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = new std::string(*player.name);
    this->territoriesList = new Map(*player.territoriesList);
    this->armyPool = player.armyPool;
}

/**
 * Card assignment operator
 * @param player
 * @return reference to Player
 */
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
    if (armyPool == 0) {
        this->orderList->add(order);
    }
    else {
        this->orderList->add(new Deploy(Order::OrderType::deploy));
        armyPool -= 1;
    }
    if(this->hand->getCards().size() != 0 ){
        this->hand->getCards();
        //**********call play()********************
    }
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
