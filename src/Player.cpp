#include "Player.h"

//Player methods

/**
 * Destructor
 */
Player::~Player()
{
    delete this->name;          //deallocate memory
    name = NULL;                //prevents dangling pointer errors
    delete this->hand;
    hand = NULL;                
    delete this ->orderList;
    orderList = NULL;
}

/**
 * Player default constructor
 * @param name
 */
Player::Player(const std::string &name) {
    this->name = new std::string(name);
    this->hand = new Hand();
    this->orderList = new OrderList();
}

/**
 * Player Constructor
 * @param hand
 * @param orderlist
 * @param name
 */
Player::Player(const Hand &hand, const OrderList &orderlist, const std::string &name)
{
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = new std::string(name);
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
}

/**
 * Card assignment operator
 * @param player
 * @return reference to Player
 */
Player& Player::operator= (const Player &player)
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
    this->orderList->add(order);
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
}

/**
 * Create and display territories to attack
 * @return content of territory
 */
std::vector<Territory *> Player::toAttack() {
    auto* territoriesToAttack = new std::vector<Territory*>;
    Territory* territory = new Territory(1,"Alabama",2);
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