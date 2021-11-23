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
bool Player::issueOrder(Deck* deck, Map* map,std::vector<Player*> players) {
    int armies = 0;
    int armiesNotDeployed = (this->armyPool);
    int i = 0;
    Order* order = nullptr;
    for (Territory* ownedTerr : map->getTerritoriesByPlayer(this)) {
        i++;
        std::cout << i << ": " << ownedTerr->getTerrName() << std::endl;
    }
     do {
         std::cout << "Armies left to deploy: " << armiesNotDeployed << std::endl << std::endl;

        // Ask for the territory to deploy to (get list: 1..4
        std::cout << "Select a territory to deploy armies to: ";
        int j = 0;
         std::cin >> j;
        Territory* deployToT = map->getTerritoriesByPlayer(this)[j - 1];

        // Ask for number of armies to deploy
        std::cout << "Select the number of armies to deploy: ";
        std::cin >> armies;
        order = new Deploy(Order::OrderType::deploy, this, deployToT, armies);
        attachExistingObservers(order, this->orderList->getObservers());
        this->orderList->add(order);
        armiesNotDeployed = armiesNotDeployed - armies;
        armies = 0;
    } while(armiesNotDeployed>0);
     std::string choice ="";
    while (choice != "card") {
        // Ask for choice
        std::cout << "Card <card>, Advance <advance> or End Turn <endturn>?: ";
        std::cin >> choice;
        if (choice == "advance") {
            order = advance(map,deck);
            orderList->add(order);
        } else if (choice == "card") {
            if (!this->hand->getCards().empty())
                this->hand->getCards().at(0)->play(orderList, hand, deck, this, map, players);
        }
        else if (choice == "endturn")
            return true;
    }
    while (true){
        std::cout << "Advance <advance> or End Turn <endturn>?: ";
        std::cin >> choice;
        if (choice == "advance") {
            order = advance(map,deck);
            orderList->add(order);
        }
        else if (choice == "endturn") {
            return true;
        }
    }
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
    auto neighbouringTerritories = std::vector<Territory*>();
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

Order *Player::advance(Map * map, Deck* deck) {
    Territory *sourceT = nullptr;
    Territory *destinationT = nullptr;
    // Display owned territories
    int i = 0;
    for (Territory *ownedTerr: map->getTerritoriesByPlayer(this)) {
        i++;
        std::cout << i << ": " << ownedTerr->getTerrName() << std::endl;
    }

    // Ask source territory
    std::cout << "Select a territory to mobilize armies from: ";
    std::cin >> i;
    sourceT = map->getTerritoriesByPlayer(this).at(i - 1);

    // Display territories adjacent to source territory
    i = 0;
    for (Territory *ownedTerr: sourceT->listOfAdjTerr) {
        i++;
        std::cout << i << ": " << ownedTerr->getTerrName() << std::endl;
    }
    // Ask destination territory
    std::cout << "Select a territory to mobilize armies to: " << std::endl;
    std::cin >> i;
    destinationT = map->getTerritoriesByPlayer(this).at(i - 1);

    // Ask for number of armies to deploy
    int armies = 0;
    std::cout << "Select the number of armies to deploy: ";
    std::cin >> armies;

    Order* order = new Advance(Order::OrderType::advance, deck, this, sourceT, destinationT, armies);
    attachExistingObservers(order, this->orderList->getObservers());
    return order;
}

void Player::attachExistingObservers(Subject *subject, const std::vector<Observer*>& observerList) {
    for (Observer* observer: observerList)
        subject->attach(observer);
}