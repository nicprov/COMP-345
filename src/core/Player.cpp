#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include <vector>

//Player methods

/**
 * Destructor
 */
Player::~Player()
{
    delete this->hand;
    hand = nullptr;
    delete this->orderList;
    orderList = nullptr;
}

/**
 * Player default constructor
 * Provides default values to the Player object
 * @param name string
 */
Player::Player(const std::string &name) {
    this->name = name;
    this->hand = new Hand();
    this->orderList = new OrderList();
    this->armyPool = 0;
}

/**
 * Player Constructor
 * @param hand Hand
 * @param orderlist OrderList
 * @param name string
 * @param territoryList vector of pointers to pointers
 */
Player::Player(const Hand &hand, const OrderList &orderlist, const std::string &name)
{
    this->armyPool = 0;
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = name;
}

/**
 * Player copy constructor
 * Makes a copy of Player
 * @param player Player
 */
Player::Player(const Player &player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = player.name;
    this->armyPool = player.armyPool;
}

/**
 * Player assignment operator
 * @param player Player
 * @return Player reference
 */
Player& Player::operator= (const Player& player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = player.name;
    this->armyPool = player.armyPool;
    return *this;
}

/**
 * Stream insertion operator for Player
 * @param stream Output stream
 * @param player Player
 * @return output stream
 */
std::ostream &operator<<(std::ostream &stream, const Player &player)
{
    return stream << "Player(" << player.name << "): " << *player.hand << ", " << *player.orderList << ", Army pool:" << player.armyPool;
}

/**
 * Create orders for execution
 * @param deck Deck
 * @param map Map
 * @param players vector of pointers to pointers
 */
void Player::issueOrder(Order* order) {
//    if (armyPool == 0) {
//        this->orderList->add(order);
//    }
//    else {
//        this->orderList->add(new Deploy(Order::OrderType::deploy));
//        armyPool -= 1;
//    }
//    if(!this->hand->getCards().empty()){
//        this->hand->getCards();
//        //**********call play()********************
//    }
}

/**
 * Comparison of player by looking at its type
 * @param player Player compared to
 * @return bool value of true (match) or false (does not match)
 */
bool Player::operator==(const Player &player) const {
    return this->name == player.name && *this->orderList == *player.orderList && *this->hand == *player.hand;
}

/**
 * Create and display territories to defend
 * based on territories owned
 * @return list of territories to defend
 */
std::vector<Territory*> Player::toDefend(Map& map) {
    return map.getTerritoriesByPlayer(this);
}

/**
 * Create and display territories to attack
 * based on adjacent territories
 * @return list of territories to attack
 */
std::vector<Territory *> Player::toAttack(Map& map) {
    auto neighbouringTerritories = vector<Territory*>();
    for (Territory* playerTerritory: map.getTerritoriesByPlayer(this)){
        for (Territory* neighbouringTerritory: playerTerritory->listOfAdjTerr){
            if (!(std::find(neighbouringTerritories.begin(), neighbouringTerritories.end(), neighbouringTerritory) != neighbouringTerritories.end())) // Check if territory is already in list
                neighbouringTerritories.push_back(neighbouringTerritory);
        }
    }
    return neighbouringTerritories;
}

/**
 * Get Player name
 * @return name of player
 */
std::string &Player::getName()
{
    return this->name;
}

/**
 * Get Orderlist
 * @return orderList of player
 */
OrderList &Player::getOrderList()
{
    return *this->orderList;
}

/**
 * Verifies if players have negotiation with eachother
 * @param enemy Player
 * @return true if negotiation is needed, false otherwise
 */
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