#include "Orders.h"

// Order methods

/*
 * Order destructor, gets overwritten by subclasses
 */
Order::~Order() = default;

/**
 * Order parameterized constructor
 *
 * @param orderType type of order
 */
Order::Order(const OrderType orderType)
{
    this->orderType = new OrderType(orderType);
}

/**
 *  Copy constructor for Order
 * @param order Order to copy
 */
Order::Order(const Order &order)
{
    this->orderType = new OrderType(*order.orderType);
}

/**
 * Assignment operator for Order
 *
 * @param order order to copy
 * @return reference to the copied Order
 */
Order &Order::operator= (const Order &order)
{
    this->orderType = new OrderType(*order.orderType);
    return *this;
}
/**
 * output stream operator
 * @param stream stream to output
 * @param order order to output to stream
 * @return stream to be output
 */
std::ostream &operator<<(std::ostream &stream, const Order &order)
{
    return stream << "Order(" << *order.orderType << ")";
}
/**
 * Accessor to get OrderType of an order
 *
 * @return OrderType of an order
 */
Order::OrderType &Order::getOrderType()
{
    return *this->orderType;
}
/**
 * Stream Output operator for OrderType
 * @param stream Stream to output
 * @param orderType ordertype to get value of and output to stream
 * @return Stream with ordertype value
 */
std::ostream &operator<<(std::ostream &stream, const Order::OrderType &orderType)
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
/**
 * Compare operator for Order
 *
 * @param order Order to be compared
 * @return True if the same false if not
 */
bool Order::operator==(const Order &order) const
{
    return *this->orderType == *order.orderType;
}

/**
 * Deploy destructor (overwrites Order destructor)
 */
Deploy::~Deploy() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Deploy Order
 */
Deploy::Deploy(const Order::OrderType orderType) : Order(orderType){}

/**
 * Deploy copy constructor
 *
 * @param deploy the deploy order to copy
 */
Deploy::Deploy(const Deploy &deploy): Order(deploy){}

/**
 * Assignment operator for Deploy
 * @param deploy Deploy Order to copy
 * @return Copied Deploy Order
 */
Deploy &Deploy::operator= (const Deploy &deploy)
{
    this->orderType = new OrderType(*deploy.orderType);
    return *this;
}
/**
 * Deploy Output Stream Operator
 * @param stream Output stream to display
 * @param deploy Deploy order to output
 * @return Stream to output with deploy value
 */
std::ostream &operator<<(std::ostream &stream, const Deploy &deploy)
{
    return stream << "Deploy(" << *deploy.orderType << ")";
}
/**
 * Print to console when deploy order is executed
 */
void Deploy::execute()
{
    std::cout << "Executing Deploy";
}
/**
 * Validate method for Deploy
 * @return True if OrderType is Deploy, false otherwise
 */
bool Deploy::validate()
{
    return this->getOrderType() == OrderType::deploy;
}

/**
 * Blockade destructor (overwrites Order destructor)
 */
Blockade::~Blockade() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Blockade Order
 */
Blockade::Blockade(const Order::OrderType orderType) : Order(orderType){}

/**
 * Blockage copy constructor
 *
 * @param blockage the blockade order to copy
 */
Blockade::Blockade(const Blockade &blockade): Order(blockade){}
/**
 * Assignment operator for Blockade
 * @param blockade Blockade Order to copy
 * @return Copied blockade Order
 */
Blockade &Blockade::operator= (const Blockade &blockade)
{
    this->orderType = new OrderType(*blockade.orderType);
    return *this;
}

/**
 * Blockage Output Stream Operator
 * @param stream Output stream to display
 * @param deploy Blockade order to output
 * @return Stream to output with blockade value
 */
std::ostream &operator<<(std::ostream &stream, const Blockade &blockade)
{
    return stream << "Deploy(" << *blockade.orderType << ")";
}

/**
 * Print to console when blockade order is executed
 */
void Blockade::execute() {
    std::cout << "Executing Blockade";
}

bool Blockade::validate() {
    return this->getOrderType() == OrderType::blockade;
}

/**
 * Advance destructor (overwrites Order destructor)
 */
Advance::~Advance() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Advance Order
 */
Advance::Advance(const Order::OrderType orderType) : Order(orderType){}

/**
 * Advance copy constructor
 *
 * @param advance the advance order to copy
 */
Advance::Advance(const Advance &advance): Order(advance){}
/**
 * Assignment operator for Advance
 * @param advance Advance Order to copy
 * @return Copied advance Order
 */
Advance &Advance::operator= (const Advance &advance)
{
    this->orderType = new OrderType(*advance.orderType);
    return *this;
}

/**
 * Advance Output Stream Operator
 * @param stream Output stream to display
 * @param advance Advance order to output
 * @return Stream to output with advance value
 */
std::ostream &operator<<(std::ostream &stream, const Advance &advance)
{
    return stream << "Deploy(" << *advance.orderType << ")";
}

/**
 * Print to console when advance order is executed
 */
void Advance::execute()
{
    std::cout << "Executing Advance";
}

/**
 * Validate method for Advance
 * @return True if OrderType is Advance, false otherwise
 */
bool Advance::validate()
{
    return this->getOrderType() == OrderType::advance;
}

/**
 * Bomb destructor (overwrites Order destructor)
 */
Bomb::~Bomb() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Bomb Order
 */
Bomb::Bomb(const Order::OrderType orderType) : Order(orderType){}
/**
 * Bomb copy constructor
 *
 * @param bomb the bomb order to copy
 */
Bomb::Bomb(const Bomb &bomb): Order(bomb){}
/**
 * Assignment operator for Bomb
 * @param bomb Bomb Order to copy
 * @return Copied bomb Order
 */
Bomb &Bomb::operator= (const Bomb &bomb)
{
    this->orderType = new OrderType(*bomb.orderType);
    return *this;
}

/**
 * Bomb Output Stream Operator
 * @param stream Output stream to display
 * @param bomb Bomb order to output
 * @return Stream to output with bomb value
 */
std::ostream &operator<<(std::ostream &stream, const Bomb &bomb)
{
    return stream << "Deploy(" << *bomb.orderType << ")";
}

/**
 * Print to console when bomb order is executed
 */
void Bomb::execute() {
    std::cout << "Executing Validate";
}


bool Bomb::validate() {
    return this->getOrderType() == OrderType::bomb;
}

/**
 * Airlift destructor (overwrites Order destructor)
 */
Airlift::~Airlift() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Airlift Order
 */
Airlift::Airlift(const Order::OrderType orderType) : Order(orderType){}

/**
 * Airlift copy constructor
 *
 * @param airlift the airlift order to copy
 */
Airlift::Airlift(const Airlift &airlift): Order(airlift){}
/**
 * Assignment operator for Airlift
 * @param airlift Airlift Order to copy
 * @return Copied airlift Order
 */
Airlift &Airlift::operator= (const Airlift &airlift)
{
    this->orderType = new OrderType(*airlift.orderType);
    return *this;
}

/**
 * Airlift Output Stream Operator
 * @param stream Output stream to display
 * @param airlift Airlift order to output
 * @return Stream to output with airlift value
 */
std::ostream &operator<<(std::ostream &stream, const Airlift &airlift)
{
    return stream << "Deploy(" << *airlift.orderType << ")";
}

/**
 * Print to console when airlift order is executed
 */
void Airlift::execute() {
    std::cout << "Executing Airlift";
}

bool Airlift::validate() {
    return this->getOrderType() == OrderType::airlift;
}

/**
 * Negotiate destructor (overwrites Order destructor)
 */
Negotiate::~Negotiate() = default;

/**
 * Parameterized constructor that calls superclass constructor
 * @param orderType ordertype of the Negotiate Order
 */
Negotiate::Negotiate(const Order::OrderType orderType) : Order(orderType){}

/**
 * Negotiate copy constructor
 *
 * @param negotiate the negotiate order to copy
 */
Negotiate::Negotiate(const Negotiate &negotiate): Order(negotiate){}
/**
 * Assignment operator for Negotiate
 * @param negotiate Negotiate Order to copy
 * @return Copied negotiate Order
 */
Negotiate &Negotiate::operator= (const Negotiate &negotiate)
{
    this->orderType = new OrderType(*negotiate.orderType);
    return *this;
}

/**
 * Negotiate Output Stream Operator
 * @param stream Output stream to display
 * @param deploy Negotiate order to output
 * @return Stream to output with negotiate value
 */
std::ostream &operator<<(std::ostream &stream, const Negotiate &negotiate)
{
    return stream << "Deploy(" << *negotiate.orderType << ")";
}

/**
 * Print to console when negotiate order is executed
 */
void Negotiate::execute()
{
    std::cout << "Executing Negotiate";
}

/**
 * Validate method for Negotiate
 * @return True if OrderType is Negotiate, false otherwise
 */
bool Negotiate::validate()
{
    return this->getOrderType() == OrderType::negotiate;
}

// OrderList methods
/**
 * Destructor for the OrderList Class
 */
OrderList::~OrderList()
{
    for (Order* order: *this->orders)
    {
        delete order;
    }
    delete this->orders;
}

/**
 * Default constructor for OrderList
 */
OrderList::OrderList()
{
    this->orders = new std::vector<Order*>;
}

/**
 * Copy Constructor for OrderList
 * @param orderList OrderList to be copied
 */
OrderList::OrderList(const OrderList &orderList)
{
    this->orders = new std::vector(*orderList.orders);
}
/**
 * OrderList assignment operator
 * @param orderList OrderList to be copied
 * @return Copy of orderList to assign
 */
OrderList &OrderList::operator=(const OrderList &orderList)
{
    this->orders = new std::vector(*orderList.orders);
    return *this;
}
/**
 * Stream output operator for OrderList
 * @param stream stream to be output
 * @param orderList OrderList to stream values of
 * @return Stream of orderlist values
 */
std::ostream &operator<<(std::ostream &stream, const OrderList &orderList)
{
    stream << "OrderList[";
    int counter = 1;
    for (Order* order: *orderList.orders){
        if (counter++ < orderList.orders->size())
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
void OrderList::add(Order *order)
{
    this->orders->push_back(order);
}

/**
 * Remove method for OrderList
 * @param index index of order to be removed from OrderList
 */
void OrderList::remove(int index)
{
    if (index > 0 && index < this->orders->size()){
        Order* order = this->orders->at(index);
        this->orders->erase(this->orders->begin() + index);
        delete order;
    } else
        throw std::runtime_error("Cannot remove order, index out of range");
}
/**
 * Move method for OrderList, moves order position in the list
 * @param order Order to be moved
 * @param newIndex index to move order to
 * @param oldIndex original index of order
 */
void OrderList::move(Order *order, int newIndex, int oldIndex)
{
    if(newIndex < this->orders->size()) {
        switch (order->getOrderType()) {
            case 1:
                this->orders->insert(this->orders->begin() + newIndex, dynamic_cast<Deploy*>(order));
                break;
            case 2:
                this->orders->insert(this->orders->begin() + newIndex, dynamic_cast<Advance*>(order));
                break;
            case 3:
                this->orders->insert(this->orders->begin() + newIndex, dynamic_cast<Bomb*>(order));
                break;
            case 4:
                this->orders->insert(this->orders->begin() + newIndex, dynamic_cast<Blockade*>(order));
                break;
            case 5:
                this->orders->insert(this->orders->begin() + newIndex, dynamic_cast<Airlift*>(order));
                break;
            case 6:
                this->orders->insert(this->orders->begin() + newIndex, dynamic_cast<Negotiate*>(order));
                break;
            default:
                throw std::runtime_error("Invalid Order Type");
        }
        this->orders->erase(this->orders->begin() + (oldIndex + 1));
    }
    else
        throw std::runtime_error("Invalid index");
}

/**
 * Accessor for OrderList
 * @return vector of order pointers
 */
std::vector<Order*> OrderList::getOrders() {
    return *this->orders;
}

/**
 * Compare operator for OrderList
 * @param orderList orderlist to compare
 * @return True if orderlist is the same, false otherwise
 */
bool OrderList::operator==(const OrderList &orderList) const {
    return *this->orders == *orderList.orders;
}
