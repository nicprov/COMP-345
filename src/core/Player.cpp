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
Player::Player(const std::string &name)
{
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
void Player::issueOrder(Deck* deck, Map* map, std::vector<Player*> players)
{
    // Issue deploy orders while there are armies to deploy
    std::cout << "Issuing deploy orders..." << std::endl << std::endl;
    issueDeployOrders(map);

    // Issue advance orders
    std::cout << std::endl << "Issuing advance orders and playing cards..." << std::endl << std::endl;
    issueAdvanceOrders(map, deck, players);
}

/**
 * Comparison of player by looking at its type
 * @param player Player compared to
 * @return bool value of true (match) or false (does not match)
 */
bool Player::operator==(const Player &player) const
{
    return this->name == player.name && *this->orderList == *player.orderList && *this->hand == *player.hand;
}

/**
 * Create and display territories to defend
 * based on territories owned
 * @return list of territories to defend
 */
std::vector<Territory*> Player::toDefend(Map* map)
{
    return map->getTerritoriesByPlayer(this);
}

/**
 * Create and display territories to attack
 * based on adjacent territories
 * @return list of territories to attack
 */
std::vector<Territory *> Player::toAttack(Map* map)
{
    auto neighbouringTerritories = std::vector<Territory*>();
    for (Territory* playerTerritory: map->getTerritoriesByPlayer(this)){
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
        if (orderList->getOrders().at(i)->getOrderType() == 6)
            if (dynamic_cast<Negotiate*>(orderList->getOrders().at(i))->getEnemy() == enemy)
                return true;
    return false;
}

Order* Player::advance(Map* map, Deck* deck)
{
    Order* order;
    int index = 1;
    int territoryFromIndex;
    int territoryToIndex;
    int armiesToDeploy;
    Territory* territoryFrom;
    Territory* territoryTo;
    int choice;

    std::cout << std::endl << "Choose which kind of mobilization you would like:" << std::endl;
    std::cout << "1. Move armies to defend" << std::endl;
    std::cout << "2. Move armies to attack" << std::endl;
    std::cout << "Select an option: ";

    getValidatedInput(choice, 1, 2);

    for (Territory* territory: this->toDefend(map))
        std::cout << index++ << ": " << territory->getTerrName() << " (armies: " << territory->getNumberOfArmies() << ")" << std::endl;

    std::cout << "Select a territory to mobilize armies from: ";
    getValidatedInput(territoryFromIndex, 1, this->toDefend(map).size());
    territoryFrom = this->toDefend(map).at(territoryFromIndex-1);

    if (choice == 1) {
        index = 1;
        for (Territory* territory: this->toDefend(map))
            std::cout << index++ << ": " << territory->getTerrName() << " (armies: " << territory->getNumberOfArmies() << ")" << std::endl;

        std::cout << "Select a territory to mobilize armies to: ";
        getValidatedInput(territoryToIndex, 1, this->toDefend(map).size());
        territoryTo = this->toDefend(map).at(territoryToIndex-1);
    } else {
        index = 1;
        for (Territory* territory: this->toAttack(map))
            std::cout << index++ << ": " << territory->getTerrName() << " (armies: " << territory->getNumberOfArmies() << ")" << std::endl;

        std::cout << "Select a territory to mobilize armies to: " << std::endl;
        getValidatedInput(territoryToIndex, 1, this->toAttack(map).size());
        territoryTo = this->toDefend(map).at(territoryToIndex-1);
    }

    std::cout << "Select the number of armies to deploy to " << territoryTo->getTerrName() << ": ";
    getValidatedInput(armiesToDeploy, 1, territoryFrom->getNumberOfArmies());

    order = new Advance(Order::OrderType::advance, deck, this, territoryFrom, territoryTo, armiesToDeploy);
    attachExistingObservers(order, this->orderList->getObservers());
    return order;
}

void Player::issueDeployOrders(Map* map)
{
    Order* order;
    Territory* territoryToDeployTo;
    int armiesDeployed = 0;

    // Issue deploy orders
    while (armiesDeployed < this->armyPool){
        int numArmiesToDeploy = 0;
        int territoryToDeployArmies = 0;

        // List territories available to deploy orders on
        int index = 1;
        for (Territory* ownedTerr : this->toDefend(map))
            std::cout << index++ << ": " << ownedTerr->getTerrName() << std::endl;

        std::cout << std::endl << "Select a territory to deploy armies to: ";
        getValidatedInput(territoryToDeployArmies, 1, (this->toDefend(map).size()));

        territoryToDeployTo = this->toDefend(map).at(territoryToDeployArmies-1);

        std::cout << "Select the number of armies (" << (this->armyPool-armiesDeployed) << " armies left to deploy) to deploy to " << territoryToDeployTo->getTerrName() << " : ";
        getValidatedInput(numArmiesToDeploy, 1, (this->armyPool-armiesDeployed));

        // Create new order
        order = new Deploy(Order::OrderType::deploy, this, territoryToDeployTo, numArmiesToDeploy);

        // Attach log observer to order
        attachExistingObservers(order, this->orderList->getObservers());

        // Add order to orderList
        this->orderList->add(order);

        armiesDeployed += numArmiesToDeploy;
    }
}

void Player::issueAdvanceOrders(Map* map, Deck* deck, std::vector<Player*> players){
    Order* order;
    bool isCardPlayed = false;
    while (true) {
        std::string choice;
        if (!isCardPlayed && this->hand->getCards().size() > 0)
            std::cout << "Card <card>, Advance <advance> or End Turn <endturn>?: ";
        else
            std::cout << "Advance <advance> or End Turn <endturn>?: ";
        std::cin >> choice;
        if (choice == "card"){
            if (!this->hand->getCards().empty()) {
                isCardPlayed = true;
                int index = 1;
                int cardIndex;
                std::cout << std::endl << "Cards available to play: " << std::endl;
                for (Card* card: this->hand->getCards())
                    std::cout << index++ << ": " << *card << std::endl;
                std::cout << "Select a card to play: ";
                getValidatedInput(cardIndex, 1, this->hand->getCards().size());
                this->hand->getCards().at(cardIndex-1)->play(deck, this, map, players);
            } else
                std::cout << "\x1B[31m" << "No cards to play" << "\033[0m" << std::endl;
        } else if (choice == "advance") {
            order = advance(map,deck);
            orderList->add(order);
        } else if (choice == "endturn") {
            break;
        } else
            std::cout << "\x1B[31m" << "Invalid choice." << "\033[0m" << std::endl;
    }
}


void Player::attachExistingObservers(Subject *subject, const std::vector<Observer*>& observerList)
{
    for (Observer* observer: observerList)
        subject->attach(observer);
}


void getValidatedInput(int& choice, int min, int max)
{
    while (choice < min or choice > max){
        if(!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\x1B[31m" << "Invalid input, try again: " << "\033[0m";
        } else if (choice < min or choice > max)
            std::cout << "\x1B[31m" << "Choice out of range, must be between " << min << ", and " << max << " : " << "\033[0m";
    }
}