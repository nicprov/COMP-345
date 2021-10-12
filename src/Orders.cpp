#include "Orders.h"

// Order methods
Order::Order(const OrderType orderType)
{
    this->orderType = new OrderType(orderType);
}

Order::Order(const Order &order)
{
    this->orderType = new OrderType(*order.orderType);
}

Order &Order::operator= (const Order &order)
{
    this->orderType = new OrderType(*order.orderType);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Order &order)
{
    return stream << "Order(" << *order.orderType << ")";
}

Order::OrderType &Order::getOrderType()
{
    return *this->orderType;
}

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

bool Order::operator==(const Order &order) const
{
    return *this->orderType == *order.orderType;
}

bool Order::validate()
{
    switch (*this->orderType) {
        case deploy:
        case advance:
        case bomb:
        case blockade:
        case airlift:
        case negotiate:
            std::cout << "Valid order";
            return true;
        default:
            std::cout << "Invalid order";
            return false;
    }
}

void Order::execute()
{
    switch (*this->orderType) {
        case deploy:
            std::cout << "Executing Deploy";
            break;
        case advance:
            std::cout << "Executing Advance";
            break;
        case bomb:
            std::cout << "Executing Bomb";
            break;
        case blockade:
            std::cout << "Executing Blockade";
            break;
        case airlift:
            std::cout << "Executing Airlift";
            break;
        case negotiate:
            std::cout << "Executing Negotiate";
            break;
        default:
            std::cout << "Invalid order";
            break;
    }
}

Deploy::Deploy(const Order::OrderType orderType) : Order(orderType){}

Deploy::Deploy(const Deploy &deploy): Order(deploy){}

Deploy &Deploy::operator= (const Deploy &deploy)
{
    this->orderType = new OrderType(*deploy.orderType);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Deploy &deploy)
{
    return stream << "Deploy(" << *deploy.orderType << ")";
}

void Deploy::execute()
{
    std::cout << "Executing Deploy";
}

bool Deploy::validate()
{
    return this->getOrderType() == OrderType::deploy;
}

Blockade::Blockade(const Order::OrderType orderType) : Order(orderType){}

Blockade::Blockade(const Blockade &blockade): Order(blockade){}

Blockade &Blockade::operator= (const Blockade &blockade)
{
    this->orderType = new OrderType(*blockade.orderType);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Blockade &blockade)
{
    return stream << "Deploy(" << *blockade.orderType << ")";
}

void Blockade::execute() {
    std::cout << "Executing Blockade";
}

bool Blockade::validate() {
    return this->getOrderType() == OrderType::blockade;
}

Advance::Advance(const Order::OrderType orderType) : Order(orderType){}

Advance::Advance(const Advance &advance): Order(advance){}

Advance &Advance::operator= (const Advance &advance)
{
    this->orderType = new OrderType(*advance.orderType);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Advance &advance)
{
    return stream << "Deploy(" << *advance.orderType << ")";
}

void Advance::execute()
{
    std::cout << "Executing Advance";
}

bool Advance::validate()
{
    return this->getOrderType() == OrderType::advance;
}

Bomb::Bomb(const Order::OrderType orderType) : Order(orderType){}

Bomb::Bomb(const Bomb &bomb): Order(bomb){}

Bomb &Bomb::operator= (const Bomb &bomb)
{
    this->orderType = new OrderType(*bomb.orderType);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Bomb &bomb)
{
    return stream << "Deploy(" << *bomb.orderType << ")";
}

void Bomb::execute() {
    std::cout << "Executing Validate";
}

bool Bomb::validate() {
    return this->getOrderType() == OrderType::bomb;
}

Airlift::Airlift(const Order::OrderType orderType) : Order(orderType){}

Airlift::Airlift(const Airlift &airlift): Order(airlift){}

Airlift &Airlift::operator= (const Airlift &airlift)
{
    this->orderType = new OrderType(*airlift.orderType);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Airlift &airlift)
{
    return stream << "Deploy(" << *airlift.orderType << ")";
}

void Airlift::execute() {
    std::cout << "Executing Airlift";
}

bool Airlift::validate() {
    return this->getOrderType() == OrderType::airlift;
}

Negotiate::Negotiate(const Order::OrderType orderType) : Order(orderType){}

Negotiate::Negotiate(const Negotiate &negotiate): Order(negotiate){}

Negotiate &Negotiate::operator= (const Negotiate &negotiate)
{
    this->orderType = new OrderType(*negotiate.orderType);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Negotiate &negotiate)
{
    return stream << "Deploy(" << *negotiate.orderType << ")";
}

void Negotiate::execute()
{
    std::cout << "Executing Negotiate";
}

bool Negotiate::validate()
{
    return this->getOrderType() == OrderType::negotiate;
}

// OrderList methods
OrderList::~OrderList()
{
    for (Order* order: *this->orders)
    {
        delete order;
    }
    delete this->orders;
}

OrderList::OrderList()
{
    this->orders = new std::vector<Order*>;
}

OrderList::OrderList(const OrderList &orderList)
{
    this->orders = new std::vector(*orderList.orders);
}

OrderList &OrderList::operator=(const OrderList &orderList)
{
    this->orders = new std::vector(*orderList.orders);
    return *this;
}

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

void OrderList::add(Order *order)
{
    this->orders->push_back(order);
}

void OrderList::remove(int index)
{
    if (index > 0 && index < this->orders->size()){
        Order* order = this->orders->at(index);
        this->orders->erase(this->orders->begin() + index);
        delete order;
    } else
        throw std::runtime_error("Cannot remove order, index out of range");
}

void OrderList::move(Order *order, int newIndex, int oldIndex)
{
    if(newIndex < this->orders->size()) {
        this->orders->insert(this->orders->begin() + newIndex, new Order(*order));
        this->orders->erase(this->orders->begin() + (oldIndex - 1));
    }
    else
        throw std::runtime_error("Invalid index");
}

std::vector<Order*> OrderList::getOrders() {
    return *this->orders;
}

bool OrderList::operator==(const OrderList &orderList) const {
    return *this->orders == *orderList.orders;
}
