#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

const boost::unordered_map<Order::OrderType, std::string> Order::orderTypeMapping = boost::assign::map_list_of(OrderType::deploy, "deploy")
    (OrderType::advance, "advance") (OrderType::bomb, "bomb") (OrderType::blockade, "blockade") (OrderType::airlift, "airlift") (OrderType::negotiate, "negotiate");

// Order methods
/*
 * Order destructor, gets overwritten by subclasses
 */
/**
 * Order parameterized constructor
 * @param orderType type of order
 */
Order::Order(Order::OrderType orderType)
{
    this->orderType = new OrderType(orderType);
}

/**
 *  Copy constructor for Order
 * @param order Order to copy
 */
Order::Order(const Order& order): Subject(order) {
    this->orderType = new OrderType(*order.orderType);
}

/**
 * Assignment operator for Order
 *
 * @param order order to copy
 * @return reference to the copied Order
 */
Order& Order::operator= (const Order& order)
{
    if (this != &order){
        delete this->orderType;
        this->orderType = new OrderType(*order.orderType);
    }
    return *this;
}

/**
 * output stream operator
 * @param stream stream to output
 * @param order order to output to stream
 * @return stream to be output
 */
std::ostream& operator<<(std::ostream& stream, const Order& order)
{
    return stream << "Order(" << *order.orderType << ")";
}

/**
 * Accessor to get OrderType of an order
 *
 * @return OrderType of an order
 */
Order::OrderType& Order::getOrderType()
{
    return *this->orderType;
}
/**
 * Stream Output operator for OrderType
 * @param stream Stream to output
 * @param orderType ordertype to get value of and output to stream
 * @return Stream with ordertype value
 */
std::ostream& operator<<(std::ostream& stream, const Order::OrderType& orderType)
{
    return stream << Order::orderTypeMapping.at(orderType);
}

/**
 * Compare operator for Order
 * @param order Order to be compared
 * @return True if the same false if not
 */
bool Order::operator==(const Order& order) const
{
    return *this->orderType == *order.orderType;
}

/**
 * Defines what is being logged
 * @return
 */
std::string Order::stringToLog()
{
    return "Order Executed: " + Order::orderTypeMapping.at(this->getOrderType());
}

//************************************************************************* DEPLOY *******************************************************************************************

/**
 * Deploy destructor (overwrites Order destructor)
 */
Deploy::~Deploy() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Deploy Order
 * @param player player issuing the deploy order
 * @param territory territory to deploy armies to
 * @param numOfArmies number of armies to deploy
 */
Deploy::Deploy(Player* player, Territory* territory, int numOfArmies) : Order(Order::OrderType::deploy)
{
    this->player = player;
    this->territory = territory;
    this->numOfArmies = numOfArmies;
}

/**
 * Deploy copy constructor
 *
 * @param deploy the deploy order to copy
 */
Deploy::Deploy(const Deploy& deploy) : Order(deploy)
{
    this->territory = new Territory(*deploy.territory);
    this->numOfArmies = deploy.numOfArmies;
}

/**
 * Assignment operator for Deploy
 * @param deploy Deploy Order to copy
 * @return Copied Deploy Order
 */
Deploy& Deploy::operator= (const Deploy& deploy)
{
    if (this != &deploy){
        delete this->orderType;
        this->orderType = new OrderType(*deploy.orderType);
        delete this->territory;
        this->territory = new Territory(*deploy.territory);
        this->numOfArmies = deploy.numOfArmies;
    }
    return *this;
}

/**
 * Deploy Output Stream Operator
 * @param stream Output stream to display
 * @param deploy order to output
 * @return Stream to output with deploy value
 */
std::ostream& operator<<(std::ostream& stream, const Deploy& deploy)
{
    return stream << "Deploy(" << *deploy.orderType << ")";
}

/**
 * Execute if validate returns true
 * Deploy a number of armies from reinforcements to a desired territory owned by the player
 */
void Deploy::execute()
{
    if (validate())
    {
        notify(this);
        player->armyPool -= numOfArmies;
        territory->addTroops(numOfArmies);
        std::cout << "Deploy Order: Deploying " << numOfArmies << " armies to " << territory->getTerrName() << "." << std::endl;
    }
}

/**
 * Validate method for Deploy
 * @return True if OrderType is Deploy, false otherwise
 */
bool Deploy::validate()
{
    if (territory->getOwner() == player && this->player->armyPool >= numOfArmies)
    {
        std::cout << "Deploy order validated." << std::endl;
        return true;
    }
    if (this->player->armyPool < this->numOfArmies) {
        std::cout << "Deploy order is invalid. Player (" << player->getName() << ") does not have sufficient armies to deploy to territory (" << this->territory->getTerrName() << ")." << std::endl;
        return false;
    }
    std::cout << "Deploy order is invalid. Player (" << player->getName() << ") does not own territory (" << territory->getTerrName() << ")." << std::endl;
    return false;
}

//************************************************************************* BLOCKADE *******************************************************************************************

/**
 * Blockade destructor (overwrites Order destructor)
 */
Blockade::~Blockade() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Blockade Order
 * @param player player issuing the blockade
 * @param target targetted territory
 */
Blockade::Blockade(Player* player, Territory* target, std::vector<Player*>& players) : Order(Order::OrderType::blockade)
{
    this->player = player;
    this->target = target;
    this->players = players;
}

/**
 * Blockade copy constructor
 * @param blockage the blockade order to copy
 */
Blockade::Blockade(const Blockade &blockade) : Order(blockade)
{
    this->player = new Player(*blockade.player);
    this->target = new Territory(*blockade.target);
    this->players = blockade.players;
}

/**
 * Assignment operator for Blockade
 * @param blockade Blockade Order to copy
 * @return Copied blockade Order
 */
Blockade& Blockade::operator= (const Blockade &blockade)
{
    if (this != &blockade){
        delete this->orderType;
        this->orderType = new OrderType(*blockade.orderType);
        delete this->target;
        this->target = new Territory(*blockade.target);
        delete this->player;
        this->player = new Player(*blockade.player);
        this->players = blockade.players;
    }
    return *this;
}

/**
 * Blockage Output Stream Operator
 * @param stream Output stream to display
 * @param deploy Blockade order to output
 * @return Stream to output with blockade value
 */
std::ostream& operator<<(std::ostream & stream, const Blockade & blockade)
{
    return stream << "Deploy(" << *blockade.orderType << ")";
}

/**
 * Execute method if validate() returns true
 * Doubles the amount of armies in a territory chosen by the player and makae the owner a neutral player
 */
void Blockade::execute()
{
    if (validate())
    {
        notify(this);
        target->addTroops(target->getNumberOfArmies()); // Double players
        bool foundNeutral = false;
        for (Player* _player: this->players)
            if (_player->getStrategyType() == PlayerStrategy::neutral) {
                target->setOwner(_player);
                foundNeutral = true;
                break;
            }
        if (!foundNeutral)
            target->setOwner(new Player("Neutral", PlayerStrategy::neutral));
        std::cout << "Blockade order: Blockading " << target->getTerrName() << " territory, doubling its forces and making it neutral. " << target->getTerrName() << " now has " << target->getNumberOfArmies() << " \narmies and belongs to " << target->getOwner()->getName() << std::endl;
    }
}

/**
 * Validate method for Blockade class, validating the owner of the target territory is myself
 * @return true if player owns the territory and if palyer has the blocked card
 */
bool Blockade::validate()
{
    if (target->getOwner() == player)
    {
        std::cout << "Blockade order validated." << std::endl;
        return true;
    }
    std::cout << "Blockade order is invalid. Player (" << player->getName() << ") does not own territory (" << target->getTerrName() << ")." << std::endl;
    return false;
}

//************************************************************************* ADVANCE *******************************************************************************************

/**
 * Advance destructor (overwrites Order destructor)
 */
Advance::~Advance() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Advance Order
 * @param deck deck of the game
 * @param player player issuing the advance
 * @param source source territory owned by the player
 * @param target targetted territory
 * @param numOfArmies number of armies
 */
Advance::Advance(Deck* deck, Player* player, Territory* source, Territory* target, int numOfArmies) : Order(Order::OrderType::advance)
{
    this->deck = deck;
    this->player = player;
    this->source = source;
    this->target = target;
    this->numOfArmies = numOfArmies;
}

/**
 * Advance copy constructor
 * @param advance the advance order to copy
 */
Advance::Advance(const Advance &advance) : Order(advance)
{
    this->deck = new Deck(*advance.deck);
    this->player = new Player(*advance.player);
    this->source = new Territory(*advance.source);
    this->target = new Territory(*advance.target);
    this->numOfArmies = advance.numOfArmies;
}

/**
 * Assignment operator for Advance
 * @param advance Advance Order to copy
 * @return Copied advance Order
 */
Advance& Advance::operator= (const Advance &advance)
{
    if (this != &advance) {
        delete this->orderType;
        this->orderType = new OrderType(*advance.orderType);
        delete this->source;
        this->source = new Territory(*advance.source);
        delete this->target;
        this->target = new Territory(*advance.target);
        this->numOfArmies = advance.numOfArmies;
    }
    return *this;
}

/**
 * Advance Output Stream Operator
 * @param stream Output stream to display
 * @param advance Advance order to output
 * @return Stream to output with advance value
 */
std::ostream& operator<<(std::ostream & stream, const Advance & advance)
{
    return stream << "Advance(" << *advance.orderType << ")";
}

/**
 * Excutes if player has no negotiations and validate returns true
 * If player owns territory advancing to then armies are moved from one territory to the next.
 * If not, war between players, if the player wins they draw a card
 */
void Advance::execute()
{
    if (validate())
    {
        notify(this);

        // Check if neutral player is being attacked, change to aggressive player if so
        if (target->getOwner()->getStrategyType() == PlayerStrategy::neutral) {
            std::cout << "Neutral player got attacked, changing to aggressive player";
            target->getOwner()->playerStrategy = new AggressivePlayerStrategy(this->player);
        }

        if (target->getOwner() == player)
        {
            source->removeTroops(numOfArmies);
            target->addTroops(numOfArmies);

            std::cout << "Advance order: Advancing " << numOfArmies << " armies from " << source->getTerrName() << " to " << target->getTerrName() << "." << std::endl;
        }
        else if (!player->hasNegotiationWith(target->getOwner()))
        {
            srand(time(nullptr));

            while (target->getNumberOfArmies() > 0 and source->getNumberOfArmies() > 0)
            {
                if (((1 + rand()) % 10) <= 6)
                    target->removeTroops(1);
                if (((1 + rand()) % 10) <= 7)
                    source->removeTroops(1);
            }

            if (target->getNumberOfArmies() == 0)
            {
                target->setOwner(player);
                target->addTroops(source->getNumberOfArmies());
                source->removeTroops(source->getNumberOfArmies());
                Card* newCard = deck->draw();
                player->hand->addCard(newCard);
                std::cout << "Advance order: You Attacked and WON! Advancing " << target->getNumberOfArmies() << " armies from " << source->getTerrName() << " to " << target->getTerrName() << ", " << target->getOwner()->getName() << " now owns this territory. You also picked up a new card: " << newCard->getType() << std::endl;
            }
            if (source->getNumberOfArmies() == 0)
                std::cout << "Advance order: You Attacked and LOST! You are left with 0 armies on " << source->getTerrName() << "." << std::endl;
        }
        else
            std::cout << "Advance order invalid: execute() method fails to execute due to negotiations." << std::endl;
    }
}

/**
 * Validate method for Advance
 * @return True if player owns source territory and target territory is adjacent to the source territory, false otherwise
 */
bool Advance::validate()
{
    if (source->getOwner() == player && source->isAdjacent(target->getTerrName()) && source->getNumberOfArmies() >= this->numOfArmies)
    {
        std::cout << "Advance order validated." << std::endl;
        return true;
    }
    if (source->getNumberOfArmies() < this->numOfArmies){
        std::cout << "Advance order is invalid. Source territory (" << source->getTerrName() << ") does not have enough armies to advance to target territory (" << target->getTerrName() << ")" << std::endl;
        return false;
    }
    std::cout << "Advance order is invalid. Player (" << player->getName() << ") does not own source territory (" << source->getTerrName() << "), or the source territory is not adjacent to the target (" << target->getTerrName() << ")" << std::endl;
    return false;
}

//************************************************************************* BOMB *******************************************************************************************

/**
 * Bomb destructor (overwrites Order destructor)
 */
Bomb::~Bomb() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Bomb Order
 * @param player Player of the Bomb Order
 * @param target Territory targetted by the Bomb Order
 */
Bomb::Bomb(Player* player, Territory* target) : Order(Order::OrderType::bomb)
{
    this->player = player;
    this->target = target;
}

/**
 * Bomb copy constructor
 * @param bomb the bomb order to copy
 */
Bomb::Bomb(const Bomb &bomb) : Order(bomb)
{
    this->player = new Player(*bomb.player);
    this->target = new Territory(*bomb.target);
}

/**
 * Assignment operator for Bomb
 * @param bomb Bomb Order to copy
 * @return Copied bomb Order
 */
Bomb& Bomb::operator= (const Bomb& bomb)
{
    if (this != &bomb){
        delete this->orderType;
        this->orderType = new OrderType(*bomb.orderType);
        delete this->target;
        this->target = new Territory(*bomb.target);
    }
    return *this;
}

/**
 * Bomb Output Stream Operator
 * @param stream Output stream to display
 * @param bomb Bomb order to output
 * @return Stream to output with bomb value
 */
std::ostream& operator<<(std::ostream & stream, const Bomb & bomb)
{
    return stream << "Deploy(" << *bomb.orderType << ")";
}

/**
* Execute if player has no negotiations and validate returns true
* Removes half the armies from the targetted territory
*/
void Bomb::execute()
{
    if (validate()) {
        // Check if neutral player is being attacked, change to aggressive player if so
        if (target->getOwner()->getStrategyType() == PlayerStrategy::neutral) {
            std::cout << "Neutral player got attacked, changing to aggressive player";
            target->getOwner()->playerStrategy = new AggressivePlayerStrategy(this->player);
        }

        if (!player->hasNegotiationWith(target->getOwner())) {
            notify(this);
            std::cout << "Bomb order executed." << std::endl;
            target->removeTroops(target->getNumberOfArmies() / 2);
            std::cout << "Bomb order: Bombing " << target->getTerrName() << " territory, reducing 1/2 of its forces. " << target->getTerrName() << " now has " << target->getNumberOfArmies() << " armies left." << std::endl;
        } else
            std::cout << "Bomb execute() failed. Cannot bomb a player that you're in negotiations with.";
    }
}

/**
*Validate method for Bomb class, validating the currentand next territories are adjacent
* @return true if player has bomb card, target is not owned by player and target territory is adjacent to a territory owned by the player, false otherwise.
*/
bool Bomb::validate()
{
    if (target->getOwner() != player) {
        for (Territory* targetTerritory: this->target->listOfAdjTerr){
            if (targetTerritory->getOwner() == player)
            {
                std::cout << "Bomb order validated." << std::endl;
                return true;
            }
        }
    }
    std::cout << "Bomb order is invalid. Player (" << player->getName() << ") owns the target territory (" << target->getTerrName() << "). You cannot attack your own territory." << std::endl;
    return false;
}

//************************************************************************* AIRLIFT *******************************************************************************************

/**
 * Airlift destructor (overwrites Order destructor)
 */
Airlift::~Airlift() = default;
/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Airlift Order
 * @param player player issuing the airlift
 * @param source source territory owned by the player
 * @param target targetted territory
 * @param numOfArmies number of armies
 */
Airlift::Airlift(Player* player, Territory* source, Territory* target, int numOfArmies) : Order(Order::OrderType::airlift)
{
    this->player = player;
    this->source = source;
    this->target = target;
    this->numOfArmies = numOfArmies;
}

/**
 * Airlift copy constructor
 * @param airlift the airlift order to copy
 */
Airlift::Airlift(const Airlift &airlift) : Order(airlift)
{
    this->player = new Player(*airlift.player);
    this->source = new Territory(*airlift.source);
    this->target = new Territory(*airlift.target);
    this->numOfArmies = airlift.numOfArmies;
}

/**
 * Assignment operator for Airlift
 * @param airlift Airlift Order to copy
 * @return Copied airlift Order
 */
Airlift& Airlift::operator= (const Airlift &airlift)
{
    if (this != &airlift){
        delete this->player;
        this->player = new Player(*airlift.player);
        delete this->source;
        this->source = new Territory(*airlift.source);
        delete this->target;
        this->target = new Territory(*airlift.target);
        this->numOfArmies = airlift.numOfArmies;
    }
    return *this;
}

/**
 * Airlift Output Stream Operator
 * @param stream Output stream to display
 * @param airlift Airlift order to output
 * @return Stream to output with airlift value
 */
std::ostream& operator<<(std::ostream & stream, const Airlift & airlift)
{
    return stream << "Airlift(" << *airlift.orderType << ")";
}

/**
 * Execute if validate returns true
 * Adds a number of armies to a territory owned by the player from another one of their territories
 */
void Airlift::execute()
{
    if (validate()) {
        notify(this);
        source->removeTroops(numOfArmies);
        target->addTroops(numOfArmies);
        std::cout << "Airlift order: Airlifting " << numOfArmies << " armies from " << source->getTerrName() << " to " << target->getTerrName() << ". " << source->getTerrName() << " has " << source->getNumberOfArmies() << " armies and " << target->getTerrName() << "has " << target->getNumberOfArmies() << " armies." << std::endl;
    }
}

/**
 * Validates the airlift order
 * @return true if the player has the airlift card abd both the source and target territories are owned by the player, false otherwise
 */
bool Airlift::validate()
{
    if (source->getOwner() == player && target->getOwner() == player && source->getNumberOfArmies() >= this->numOfArmies) {
        std::cout << "Airlift order validated." << std::endl;
        return true;
    }
    if (source->getNumberOfArmies() < this->numOfArmies) {
        std::cout << "Airlift order is invalid. Source territory (" << source->getTerrName() << ") does not have sufficient armies to deploy to target territory (" << target->getTerrName() << ")." << std::endl;
        return false;
    }
    std::cout << "Airlift order is invalid. Player (" << player->getName() << ") is not the owner of either the source (" << source->getTerrName() << "), or the target (" << target->getTerrName() << ")." << std::endl;
    return false;
}

//************************************************************************* NEGOTIATE *******************************************************************************************

/**
 * Negotiate destructor (overwrites Order destructor)
 */
Negotiate::~Negotiate() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Negotiate Order
 * @param player player issuing the negotiation
 * @param enemy player to negotiate with
 */
Negotiate::Negotiate(Player* player, Player* enemy) : Order(Order::OrderType::negotiate)
{
    this->player = player;
    this->enemy = enemy;
}

/**
 * Negotiate copy constructor
 *
 * @param negotiate the negotiate order to copy
 */
Negotiate::Negotiate(const Negotiate &negotiate) : Order(negotiate)
{
    this->player = new Player(*negotiate.player);
    this->enemy = new Player(*negotiate.enemy);
}

/**
 * Assignment operator for Negotiate
 * @param negotiate Negotiate Order to copy
 * @return Copied negotiate Order
 */
Negotiate& Negotiate::operator= (const Negotiate & negotiate)
{
    if (this != &negotiate){
        delete this->orderType;
        this->orderType = new OrderType(*negotiate.orderType);
        delete this->player;
        this->player = new Player(*negotiate.player);
        delete this->enemy;
        this->enemy = new Player(*negotiate.enemy);
    }
    return *this;
}

/**
 * Negotiate Output Stream Operator
 * @param stream Output stream to display
 * @param deploy Negotiate order to output
 * @return Stream to output with negotiate value
 */
std::ostream& operator<<(std::ostream & stream, const Negotiate & negotiate)
{
    return stream << "Deploy(" << *negotiate.orderType << ")";
}
/**
 * Execute if validate returns true
 */
void Negotiate::execute()
{
    if (validate()) {
        notify(this);
        std::cout << "Negotiate order executed." << std::endl;
        std::cout << "Negotiate order: Negotiating... No attack is being performed this turn. (do nothing)" << std::endl;
    }
}

/**
 * Validate method for Negotiate
 * @return True if player has the diplomacy card and if enemy is not the player, false otherwise
 */
bool Negotiate::validate()
{
    if (player != enemy)
    {
        std::cout << "Negotiate order validated." << std::endl;
        return true;
    }
    std::cout << "Negotiate order is invalid. You cannot negotiate with yourself." << std::endl;
    return false;
}

/**
 * get the eneny
 * @return the enemy with who player has negotiations 
 */
Player* Negotiate::getEnemy()
{
    return enemy;
}

//************************************************************************* ORDER LIST *******************************************************************************************

// OrderList methods
/**
 * Destructor for the OrderList Class
 */
OrderList::~OrderList()
{
    for (Order* order : this->orders)
    {
        switch (order->getOrderType()) {
            case Order::deploy:
                delete dynamic_cast<Deploy*>(order);
                break;
            case Order::advance:
                delete dynamic_cast<Advance*>(order);
                break;
            case Order::bomb:
                delete dynamic_cast<Bomb*>(order);
                break;
            case Order::blockade:
                delete dynamic_cast<Blockade*>(order);
                break;
            case Order::airlift:
                delete dynamic_cast<Airlift*>(order);
                break;
            case Order::negotiate:
                delete dynamic_cast<Negotiate*>(order);
                break;
        }
    }
}

/**
 * Default constructor for OrderList
 */
OrderList::OrderList(): Subject()
{
    this->orders = std::vector<Order*>();
}

/**
 * Copy Constructor for OrderList
 * @param orderList OrderList to be copied
 */
OrderList::OrderList(const OrderList &orderList): Subject(orderList) {
    this->orders = std::vector<Order*>();
    for (Order* order: orderList.orders) {
        switch (order->getOrderType()) {
            case Order::deploy:
                this->orders.push_back(new Deploy(*dynamic_cast<Deploy*>(order)));
                break;
            case Order::advance:
                this->orders.push_back(new Advance(*dynamic_cast<Advance*>(order)));
                break;
            case Order::bomb:
                this->orders.push_back(new Bomb(*dynamic_cast<Bomb*>(order)));
                break;
            case Order::blockade:
                this->orders.push_back(new Blockade(*dynamic_cast<Blockade*>(order)));
                break;
            case Order::airlift:
                this->orders.push_back(new Airlift(*dynamic_cast<Airlift*>(order)));
                break;
            case Order::negotiate:
                this->orders.push_back(new Negotiate(*dynamic_cast<Negotiate*>(order)));
                break;
        }
    }
}

/**
 * OrderList assignment operator
 * @param orderList OrderList to be copied
 * @return Copy of orderList to assign
 */
OrderList& OrderList::operator=(const OrderList &orderList)
{
    if (this != &orderList){
        for (Order* order: this->orders) {
            switch (order->getOrderType()) {
                case Order::deploy:
                    delete dynamic_cast<Deploy*>(order);
                    break;
                case Order::advance:
                    delete dynamic_cast<Advance*>(order);
                    break;
                case Order::bomb:
                    delete dynamic_cast<Bomb*>(order);
                    break;
                case Order::blockade:
                    delete dynamic_cast<Blockade*>(order);
                    break;
                case Order::airlift:
                    delete dynamic_cast<Airlift*>(order);
                    break;
                case Order::negotiate:
                    delete dynamic_cast<Negotiate*>(order);
                    break;
            }
        }
        this->orders = std::vector<Order*>();
        for (Order* order: orderList.orders) {
            switch (order->getOrderType()) {
                case Order::deploy:
                    this->orders.push_back(new Deploy(*dynamic_cast<Deploy*>(order)));
                    break;
                case Order::advance:
                    this->orders.push_back(new Advance(*dynamic_cast<Advance*>(order)));
                    break;
                case Order::bomb:
                    this->orders.push_back(new Bomb(*dynamic_cast<Bomb*>(order)));
                    break;
                case Order::blockade:
                    this->orders.push_back(new Blockade(*dynamic_cast<Blockade*>(order)));
                    break;
                case Order::airlift:
                    this->orders.push_back(new Airlift(*dynamic_cast<Airlift*>(order)));
                    break;
                case Order::negotiate:
                    this->orders.push_back(new Negotiate(*dynamic_cast<Negotiate*>(order)));
                    break;
            }
        }
    }
    return *this;
}

/**
 * Stream output operator for OrderList
 * @param stream stream to be output
 * @param orderList OrderList to stream values of
 * @return Stream of orderlist values
 */
std::ostream& operator<<(std::ostream & stream, const OrderList & orderList)
{
    stream << "OrderList[";
    int counter = 1;
    for (Order* order : orderList.orders) {
        if (counter++ < orderList.orders.size())
            stream << order->getOrderType() << ",";
        else
            stream << order->getOrderType();
    }
    stream << "]";
    return stream;
}

/**
 * Add method to add an Order to the OrderList
 * @param order order to be added to the OrderList
 */
void OrderList::add(Order * order)
{
    this->orders.push_back(order);
    notify(this);
}

/**
 * Remove method for OrderList
 * @param index index of order to be removed from OrderList
 */
void OrderList::remove(int index)
{
    if (index >= 0 && index < this->orders.size()) {
        Order* order = this->orders.at(index);
        this->orders.erase(this->orders.begin() + index);
        switch (order->getOrderType()) {
            case Order::deploy:
                delete dynamic_cast<Deploy*>(order);
                break;
            case Order::advance:
                delete dynamic_cast<Advance*>(order);
                break;
            case Order::bomb:
                delete dynamic_cast<Bomb*>(order);
                break;
            case Order::blockade:
                delete dynamic_cast<Blockade*>(order);
                break;
            case Order::airlift:
                delete dynamic_cast<Airlift*>(order);
                break;
            case Order::negotiate:
                delete dynamic_cast<Negotiate*>(order);
                break;
        }
    }
    else
        throw std::runtime_error("Cannot remove order, index out of range");
}

/**
 * Move method for OrderList, moves order position in the list
 * @param order Order to be moved
 * @param newIndex index to move order to
 * @param oldIndex original index of order
 */
void OrderList::move(Order* order, int newIndex, int oldIndex)
{
    if (newIndex < this->orders.size()) {
        switch (order->getOrderType()) {
            case Order::OrderType::negotiate:
                this->orders.insert(this->orders.begin() + newIndex, new Negotiate(*dynamic_cast<Negotiate*>(order)));
                break;
            case Order::OrderType::airlift:
                this->orders.insert(this->orders.begin() + newIndex, new Airlift(*dynamic_cast<Airlift*>(order)));
                break;
            case Order::OrderType::bomb:
                this->orders.insert(this->orders.begin() + newIndex, new Bomb(*dynamic_cast<Bomb*>(order)));
                break;
            case Order::OrderType::advance:
                this->orders.insert(this->orders.begin() + newIndex, new Advance(*dynamic_cast<Advance*>(order)));
                break;
            case Order::OrderType::blockade:
                this->orders.insert(this->orders.begin() + newIndex, new Blockade(*dynamic_cast<Blockade*>(order)));
                break;
            case Order::OrderType::deploy:
                this->orders.insert(this->orders.begin() + newIndex, new Deploy(*dynamic_cast<Deploy*>(order)));
                break;
        }
        this->orders.erase(this->orders.begin() + (oldIndex + 1));
    }
    else
        throw std::runtime_error("Invalid index");
}

/**
 * Accessor for OrderList
 * @return vector of order pointers
 */
std::vector<Order*> OrderList::getOrders() {
    return this->orders;
}

/**
 * Compare operator for OrderList
 * @param orderList orderlist to compare
 * @return True if orderlist is the same, false otherwise
 */
bool OrderList::operator==(const OrderList &orderList) const {
    int counter = 0;
    for (Order* order: orderList.orders)
        if (!(*this->orders.at(counter++) == *order))
            return false;
    return true;
}

/**
 * get size
 * @return size of orderlist
 */
int OrderList::getSize() {
    return this->orders.size();
}

/**
 * Specified what wil be logged for the order list
 * @return log string
 */
std::string OrderList::stringToLog()
{
    return "Order Issued: " + Order::orderTypeMapping.at(orders.at(this->orders.size()-1)->getOrderType());
}