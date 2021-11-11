#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include <vector>
using namespace  std;

//Player methods

/**
 * Destructor
 */
Player::~Player()
{
    delete this->name;          //deallocate memory
    delete this->hand;
    delete this ->orderList;
    delete this->territoriesList;

}

/**
 * Player default constructor
 * @param name
 */
Player::Player(const std::string &name) {
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
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = new std::string(name);
    this->territoriesList = new Map(territoriesList);

}

/**
 * Player copy constructor
 * @param player
 */
Player::Player(const Player &player)
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
Player& Player::operator=(const Player &player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = new std::string(*player.name);
    return *this;
}

/**
 * Stream insertion operator for Player
 * @param stream
 * @param player
 * @return output stream
 */
std::ostream &operator<<(std::ostream &stream, const Player &player)
{
    return stream << "Player(" << *player.name << "): " << *player.hand << ", " << *player.orderList;
}

/**
 * Add order to orderlist
 * @param order
 */
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

/**
 * Comparison of player by looking at its type
 * @param player
 * @return bool value of true (match) or false (does not match)
 */
bool Player::operator==(const Player &player) const {
    return *this->name == *player.name && *this->orderList == *player.orderList && *this->hand == *player.hand;
}

/**
 * Create and display territories to defend
 * @return content of territory
 */
std::vector<Territory *> Player::toDefend() {
    auto* territoriesToDefend = new std::vector<Territory*>;
    Territory* territory = new Territory(1,"Alabama",2);
    territoriesToDefend->push_back(territory);
    return *territoriesToDefend;
    //territry to defend and attack vector. and add to the two methods that it returns the vector. add to the list the players that they want to attack/defend
}

/**
 * Create and display territories to attack
 * @return content of territory
 */
std::vector<Territory *> Player::toAttack() {
    auto* territoriesToAttack = new std::vector<Territory*>;
    Territory* territory = new Territory(2,"Alabama",2);
    territoriesToAttack->push_back(territory);
    return *territoriesToAttack;
}

/**
 * Get Player name
 * @return name
 */
std::string &Player::getName()
{
    return *this->name;
}

/**
 * Get Orderlist
 * @return orderList
 */
OrderList &Player::getOrderList()
{
    return *this->orderList;
}