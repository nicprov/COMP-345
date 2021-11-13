#include "Orders.h"

// Order methods
Order::Order(Order::OrderType orderType)
{
    this->orderType = new OrderType(orderType);
}

Order::Order(const Order& order)
{
    this->orderType = new OrderType(*order.orderType);
}

Order& Order::operator= (const Order& order)
{
    this->orderType = new OrderType(*order.orderType);
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Order& order)
{
    return stream << "Order(" << *order.orderType << ")";
}

Order::OrderType& Order::getOrderType()
{
    return *this->orderType;
}

std::ostream& operator<<(std::ostream& stream, const Order::OrderType& orderType)
{
    switch (orderType) {
        case Order::OrderType::bomb:
            stream << "Bomb";
            break;
        case Order::OrderType::negotiate:
            stream << "Negotiate";
            break;
        case Order::OrderType::airlift:
            stream << "Airlift";
            break;
        case Order::OrderType::blockade:
            stream << "Blockade";
            break;
        case Order::OrderType::deploy:
            stream << "Deploy";
            break;
        case Order::OrderType::advance:
            stream << "Advance";
            break;
    }
    return stream;
}

bool Order::operator==(const Order& order) const
{
    return *this->orderType == *order.orderType;
}

//************************************************************************* DEPLOY *******************************************************************************************

Deploy::Deploy(const Order::OrderType orderType, Player* player, Territory* territory, int numOfArmies) : Order(orderType)
{
    this->player = player;
    this->territory = territory;
    this->numOfArmies = numOfArmies;
}

Deploy::Deploy(const Deploy& deploy) : Order(deploy)
{
    this->territory = new Territory(*deploy.territory);
    this->numOfArmies = deploy.numOfArmies;
}

Deploy& Deploy::operator= (const Deploy& deploy)
{
    this->orderType = new OrderType(*deploy.orderType);
    this->territory = new Territory(*deploy.territory);
    this->numOfArmies = deploy.numOfArmies;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Deploy& deploy)
{
    return stream << "Deploy(" << *deploy.orderType << ")";
}

/**
 * Print to console when deploy order is executed
 */
void Deploy::execute()
{
    if (validate())
    {
        notify(this);
        cout << "Deploy order executed." << endl;

        //player->removeReinforcements(numOfArmies); something like this to remove the number of armies from the total number available.
        territory->addTroops(numOfArmies);
        cout << "DEPLOY ORDER: Deploying " << numOfArmies << " armies to " << territory->getTerrName() << "." << endl;
    }
    else
    {
        cout << "Deploy order invalid: execute() method fails to execute." << endl;
    }

}
/**
 * Validate method for Deploy
 * @return True if OrderType is Deploy, false otherwise
 */
bool Deploy::validate()
{
    if (territory->getOwner() == player)
    {
        cout << "Deploy order validated." << endl;
        return true;
    }
    cout << "Deploy order is invalid." << endl;
    return false;
}
std::string Deploy::stringToLog() {
    return "Order Executed: Deploy";
}

//************************************************************************* BLOCKADE *******************************************************************************************

/**
 * Blockade destructor (overwrites Order destructor)
 */
Blockade::~Blockade() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Blockade Order
 */
Blockade::Blockade(Order::OrderType orderType, Player* player, Territory* target) : Order(orderType)
{
    this->player = player;
    this->target = target;
}

/**
 * Blockage copy constructor
 *
 * @param blockage the blockade order to copy
 */
Blockade::Blockade(const Blockade &blockade) : Order(blockade)
{
    this->target = new Territory(*blockade.target);
}

/**
 * Assignment operator for Blockade
 * @param blockade Blockade Order to copy
 * @return Copied blockade Order
 */
Blockade& Blockade::operator= (const Blockade & blockade)
{
    this->orderType = new OrderType(*blockade.orderType);
    this->target = new Territory(*blockade.target);
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
 */

void Blockade::execute()
{
    if (validate())
    {
        notify(this);
        cout << "Blockade order executed." << endl;
        target->addTroops(target->getNumberOfArmies() * 2);
        target->setOwner(new Player("Neutral")); //neutral player, come back to this when neutral player implemented
        cout << "BLOCKADE ORDER: Blockading " << target->getTerrName() << " territory, doubling its forces and making it neutral.\n";
    }
    else
        cout << "Blockade order invalid: execute() method fails to execute." << endl;
}

/**
 * Validate method for Blockade class, validating the owner of the target territory is myself
 */
bool Blockade::validate()
{
    for (int i = 0; i < player->hand->getCards().size(); i++)
    {
        if (player->hand->getCards().at(i)->getType() == Card::blockade)

        {
            if (target->getOwner() == player)
            {
                cout << "Blockade order validated." << endl;
                return true;
            }
            cout << "Blockade order is invalid." << endl;
            return false;
        }
    }
    return false;
}

std::string Blockade::stringToLog() {
    return "Order Executed: Blockade";
}


//************************************************************************* ADVANCE *******************************************************************************************

/**
 * Advance destructor (overwrites Order destructor)
 */
Advance::~Advance() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Advance Order
 */
Advance::Advance(Order::OrderType orderType, Deck* deck, Player* player, Territory* source, Territory* target, int numOfArmies) : Order(orderType)
{
    this->deck = deck;
    this->player = player;
    this->source = source;
    this->target = target;
    this->numOfArmies = numOfArmies;
}

/**
 * Advance copy constructor
 *
 * @param advance the advance order to copy
 */
Advance::Advance(const Advance &advance) : Order(advance)
{
    this->source = new Territory(*advance.source);
    this->target = new Territory(*advance.target);
    this->numOfArmies = advance.numOfArmies;
}

/**
 * Assignment operator for Advance
 * @param advance Advance Order to copy
 * @return Copied advance Order
 */
Advance& Advance::operator= (const Advance & advance)
{
    this->orderType = new OrderType(*advance.orderType);
    this->source = new Territory(*advance.source);
    this->target = new Territory(*advance.target);
    this->numOfArmies = advance.numOfArmies;
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
 * Print to console when advance order is executed
 */
void Advance::execute()
{

    if (validate())
    {
        notify(this);
        cout << "Advance order executed." << endl;

        if (target->getOwner() == player)
        {
            source->removeTroops(numOfArmies);
            target->addTroops(numOfArmies);

            cout << "ADVANCE ORDER: Advancing " << numOfArmies << " armies from " << source->getTerrName() << " to " << target->getTerrName() << "." << endl;
        }
        else if (!player->hasNegotiationWith(target->getOwner()))
        {
            srand(time(nullptr));
            
            while (target->getNumberOfArmies() > 0 || source->getNumberOfArmies() > 0)
            {
                if (rand() % 10 < 6)
                    target->removeTroops(1);

                else if (rand() % 10 < 7)
                    source->removeTroops(1);
            }

            if (target->getNumberOfArmies() == 0)
            {
                target->setOwner(player);
                target->addTroops(source->getNumberOfArmies());
                source->removeTroops(source->getNumberOfArmies());
                player->hand->addCard(deck->draw());

                cout << "ADVANCE ORDER: You Attacked and WON! Advancing " << target->getNumberOfArmies() << " armies from " << source->getTerrName() << " to " << target->getTerrName() << "." << endl;
            }
            if (source->getNumberOfArmies() == 0)
            {
                cout << "ADVANCE ORDER: You Attacked and LOST! You are left with 0 armies on " << source->getTerrName() << "." << endl;
            }
        }
        else
        {
            cout << "Advance order invalid: execute() method fails to execute due to negotiations." << endl;
        }
    }
    else
    {
        cout << "Advance order invalid: execute() method fails to execute." << endl;
    }
}

/**
 * Validate method for Advance
 * @return True if OrderType is Advance, false otherwise
 */
bool Advance::validate()
{
    if (source->getOwner() == player && source->isAdjacent(target->getTerrName()))
    {
        cout << "Advance order validated." << endl;
        return true;
    }
    cout << "Advance order is invalid." << endl;
    return false;
}


std::string Advance::stringToLog() {
    return "Order Executed: Advance";
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
Bomb::Bomb(Order::OrderType orderType, Player* player, Territory* target) : Order(orderType)
{
    this->player = player;
    this->target = target;
}
/**
 * Bomb copy constructor
 *
 * @param bomb the bomb order to copy
 */
Bomb::Bomb(const Bomb & bomb) : Order(bomb)
{
    this->target = new Territory(*bomb.target);
}

/**
 * Assignment operator for Bomb
 * @param bomb Bomb Order to copy
 * @return Copied bomb Order
 */
Bomb& Bomb::operator= (const Bomb& bomb)
{
    this->orderType = new OrderType(*bomb.orderType);
    this->target = new Territory(*bomb.target);
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
*Print to console when bomb order is executed
*/
void Bomb::execute() {

    if (!player->hasNegotiationWith(target->getOwner()))
    {
        if (validate())
        {
            notify(this);
            cout << "Bomb order executed." << endl;

            int numDestroyed = target->getNumberOfArmies() / 2;

            target->removeTroops(numDestroyed);

            cout << "BOMB ORDER: Bombing " << target->getTerrName() << " territory, reducing 1/2 of its forces.\n";
        }
        else
            cout << "Bomb order invalid: execute() method fails to execute." << endl;
    }
    else
        cout << "Bomb order invalid: execute() method fails to execute due to negotiations." << endl;

}
/**
*Validate method for Bomb class, validating the currentand next territories are adjacent
*/
bool Bomb::validate()
{
    for (int i = 0; i < player->hand->getCards().size(); i++)
    {
        if (player->hand->getCards().at(i)->getType() == Card::bomb)
        {
            if (target->getOwner() != player)
            {
                for (int i = 0; i < target->listOfAdjTerr.size(); i++)
                {
                    if (target->listOfAdjTerr.at(i)->getOwner() == player)
                    {
                        cout << "Bomb order validated." << endl;
                        return true;
                    }
                }
            }
            cout << "Bomb order is invalid." << endl;
            return false;
        }
    }
    return false;
}

std::string Bomb::stringToLog() {
    return "Order Executed: Bomb";
}


//************************************************************************* AIRLIFT *******************************************************************************************


/**
 * Airlift destructor (overwrites Order destructor)
 */
Airlift::~Airlift() = default;


/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Airlift Order
 */
Airlift::Airlift(const Order::OrderType orderType, Player* player, Territory* source, Territory* target, int numOfArmies) : Order(orderType)
{
    this->player = player;
    this->source = source;
    this->target = target;
    this->numOfArmies = numOfArmies;
}

/**
 * Airlift copy constructor
 *
 * @param airlift the airlift order to copy
 */
Airlift::Airlift(const Airlift &airlift) : Order(airlift)
{
    this->source = new Territory(*airlift.source);
    this->target = new Territory(*airlift.target);
    this->numOfArmies = airlift.numOfArmies;
}

/**
 * Assignment operator for Airlift
 * @param airlift Airlift Order to copy
 * @return Copied airlift Order
 */
Airlift& Airlift::operator= (const Airlift & airlift)
{
    this->orderType = new OrderType(*airlift.orderType);
    this->source = new Territory(*airlift.source);
    this->target = new Territory(*airlift.target);
    this->numOfArmies = airlift.numOfArmies;
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
 * Print to console when airlift order is executed
 */
void Airlift::execute()
{
    if (validate())
    {
        notify(this);
        cout << "Deploy order executed." << endl;

        source->removeTroops(numOfArmies);
        target->addTroops(numOfArmies);
        cout << "AIRLIFT ORDER: Airlifting " << numOfArmies << " armies from " << source->getTerrName() << " to " << target->getTerrName() << "." << endl;
    }
    else
    {
        cout << "Airlift order invalid: execute() method fails to execute." << endl;
    }
}

bool Airlift::validate()
{
    for (int i = 0; i < player->hand->getCards().size(); i++)
    {
        if (player->hand->getCards().at(i)->getType() == Card::airlift)
        {
            if (source->getOwner() == player && target->getOwner() == player)
            {
                cout << "Advance order validated." << endl;
                return true;
            }
            cout << "Advance order is invalid." << endl;
            return false;
        }
    }
    return false;
}

std::string Airlift::stringToLog() {
    return "Order Executed: Airlift";
}


//************************************************************************* NEGOTIATE *******************************************************************************************

/**
 * Negotiate destructor (overwrites Order destructor)
 */
Negotiate::~Negotiate() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Negotiate Order
 */
Negotiate::Negotiate(Order::OrderType orderType, Player* player, Player* enemy) : Order(orderType)
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
    this->enemy = new Player(*negotiate.enemy);
}

/**
 * Assignment operator for Negotiate
 * @param negotiate Negotiate Order to copy
 * @return Copied negotiate Order
 */
Negotiate& Negotiate::operator= (const Negotiate & negotiate)
{
    this->orderType = new OrderType(*negotiate.orderType);
    this->enemy = new Player(*negotiate.enemy);
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
 * Print to console when negotiate order is executed
 */
void Negotiate::execute()
{
    if (validate())
    {
        notify(this);
        cout << "Negotiate order executed." << endl;

        cout << "NEGOTIATE ORDER: Negotiating... No attack is being performed this turn. (do nothing)\n";
    }
    else
        cout << "Negotiate order invalid: execute() method fails to execute." << endl;
}

/**
 * Validate method for Negotiate
 * @return True if OrderType is Negotiate, false otherwise
 */
bool Negotiate::validate()
{
    for (int i = 0; i < player->hand->getCards().size(); i++)
    {
        if (player->hand->getCards().at(i)->getType() == Card::diplomacy)
        {
            if (player != enemy)
            {
                cout << "Negotiate order validated." << endl;
                return true;
            }
            cout << "Negotiate order is invalid." << endl;
            return false;
        }
    }
    return false;
}

Player* Negotiate::getEnemy()
{
    return enemy;
}

std::string Negotiate::stringToLog() {
    std::cout << "Order Executed: Negotiate" <<std::endl;
    return "Order Executed: Negotiate";
}

//************************************************************************* ORDER LIST *******************************************************************************************

// OrderList methods
OrderList::~OrderList()
{
    for (Order* order : *this->orders)
    {
        delete order;
    }
    delete this->orders;
}

OrderList::OrderList()
{
    this->orders = new std::vector<Order*>;
}

OrderList::OrderList(const OrderList & orderList)
{
    this->orders = new std::vector(*orderList.orders);
}

OrderList& OrderList::operator=(const OrderList & orderList)
{
    this->orders = new std::vector(*orderList.orders);
    return *this;
}

std::ostream& operator<<(std::ostream & stream, const OrderList & orderList)
{
    stream << "OrderList[";
    int counter = 1;
    for (Order* order : *orderList.orders) {
        if (counter++ < orderList.orders->size())
            stream << order->getOrderType() << ",";
        else
            stream << order->getOrderType();
    }
    stream << "]";
    return stream;
}

void OrderList::add(Order * order)
{
    this->orders->push_back(order);
    notify(this);
}

void OrderList::remove(int index)
{
    if (index > 0 && index < this->orders->size()) {
        Order* order = this->orders->at(index);
        this->orders->erase(this->orders->begin() + index);
        delete order;
    }
    else
        throw std::runtime_error("Cannot remove order, index out of range");
}

void OrderList::move(Order* order, int newIndex, int oldIndex)
{
    if (newIndex < this->orders->size()) {
        switch (order->getOrderType()) {
            case Order::OrderType::negotiate:
                this->orders->insert(this->orders->begin() + newIndex, new Negotiate(*dynamic_cast<Negotiate*>(order)));
                break;
            case Order::OrderType::airlift:
                this->orders->insert(this->orders->begin() + newIndex, new Airlift(*dynamic_cast<Airlift*>(order)));
                break;
            case Order::OrderType::bomb:
                this->orders->insert(this->orders->begin() + newIndex, new Bomb(*dynamic_cast<Bomb*>(order)));
                break;
            case Order::OrderType::advance:
                this->orders->insert(this->orders->begin() + newIndex, new Advance(*dynamic_cast<Advance*>(order)));
                break;
            case Order::OrderType::blockade:
                this->orders->insert(this->orders->begin() + newIndex, new Blockade(*dynamic_cast<Blockade*>(order)));
                break;
            case Order::OrderType::deploy:
                this->orders->insert(this->orders->begin() + newIndex, new Deploy(*dynamic_cast<Deploy*>(order)));
                break;
        }
        this->orders->erase(this->orders->begin() + (oldIndex + 1));
    }
    else
        throw std::runtime_error("Invalid index");
}

std::vector<Order*> OrderList::getOrders() {
    return *this->orders;
}

bool OrderList::operator==(const OrderList & orderList) const {
    return *this->orders == *orderList.orders;
}

int OrderList::getSize() {
    return this->orders->size();
}


std::string OrderList::stringToLog() {
    std::string currentOrder = std::to_string(orders->at(this->orders->size()-1)->getOrderType());
    return "Order Issued: " + currentOrder;
}
