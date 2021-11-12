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
    delete this->hand;
    hand = nullptr;
    delete this->orderList;
    orderList = nullptr;
    for(Territory* territory: *this->territoriesList ){
        delete territory;
    }

}

/**
 * Player default constructor
 * @param name
 */
Player::Player(const std::string &name) {
    this->name = name;
    this->hand = new Hand();
    this->orderList = new OrderList();
    this->armyPool = 0;
    this->territoriesList = new vector<Territory*>;
}

/**
 * Player Constructor
 * @param hand
 * @param orderlist
 * @param name
 */
Player::Player(const Hand &hand, const OrderList &orderlist, const std::string &name, vector<Territory*>* territoryList)
{
    this->armyPool = 0;
    this->hand = new Hand(hand);
    this->orderList = new OrderList(orderlist);
    this->name = name;
    this->territoriesList = new vector(*territoryList);
}

/**
 * Player copy constructor
 * @param player
 */
Player::Player(const Player &player)
{
    this->hand = new Hand(*player.hand);
    this->orderList = new OrderList(*player.orderList);
    this->name = player.name;
    this->territoriesList = new vector(*player.territoriesList);
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
    this->name = player.name;
    this->territoriesList = new vector(*player.territoriesList);
    this->armyPool = player.armyPool;
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
    return stream << "Player(" << player.name << "): " << *player.hand << ", " << *player.orderList << ", Army pool:" << player.armyPool;
}

/**
 * Add order to orderlist
 * @param order
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
 * @param player
 * @return bool value of true (match) or false (does not match)
 */
bool Player::operator==(const Player &player) const {
    return this->name == player.name && *this->orderList == *player.orderList && *this->hand == *player.hand;
}

/**
 * Create and display territories to defend
 * @return content of territory
 */
std::vector<Territory*>* Player::toDefend() {
    auto* territoriesToDefend = this->territoriesList;
    return territoriesToDefend;
}

/**
 * Create and display territories to attack
 * @return content of territory
 */
std::vector<Territory *>* Player::toAttack() {
    auto* territoriesToAttack = new std::vector<Territory*>;
    for(Territory* territory: *territoriesList){
        for(Territory* adj : territory->listOfAdjTerr){
            territoriesToAttack->push_back(adj);
        }
    }
    return territoriesToAttack;
}

/**
 * Get Player name
 * @return name
 */
std::string &Player::getName()
{
    return this->name;
}

/**
 * Get Orderlist
 * @return orderList
 */
OrderList &Player::getOrderList()
{
    return *this->orderList;
}

bool Player::hasNegotiationWith(Player* enemy)
{
    //TODO fix
    return false;
//    for (int i = 0; i < orderList->getOrders().size(); i++)
//    {
//        if (orderList->getOrders().at(i)->getOrderType() == 6)
//        {
//            if (dynamic_cast<Negotiate*>(orderList->getOrders().at(i))->getEnemy() == enemy)
//            {
//                return true;
//            }
//        }
//    }
//    return false;
}