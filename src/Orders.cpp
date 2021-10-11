#include "Orders.h"

// Order methods
Order::Order(const OrderType orderType)
{
    this->orderType = new OrderType(orderType);
}

Order::Order(const Order *order)
{
    this->orderType = new OrderType(*order->orderType);
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

void Order::execute()
{
    switch (*this->orderType) {
        case deploy:
            std::cout << "Deploy order";
            break;
        case advance:
            std::cout << "Advance order";
            break;
        case bomb:
            std::cout << "Bomb order";
            break;
        case blockade:
            std::cout << "Blockade order";
            break;
        case airlift:
            std::cout << "Airlift order";
            break;
        case negotiate:
            std::cout << "Negotiate order";
            break;
        default:
            std::cout << "Invalid order";
            break;
    }
}

void Order::validate()
{
    switch (*this->orderType) {
        case deploy:
        case advance:
        case bomb:
        case blockade:
        case airlift:
        case negotiate:
            std::cout << "Valid order";
            break;
        default:
            std::cout << "Invalid order";
            break;
    }
}

std::ostream &operator<<(std::ostream &stream, const Order::OrderType &orderType) {
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
            stream << "Depoy";
            break;
        case Order::OrderType::advance:
            stream << "Advance";
            break;
    }
    return stream;
}

bool Order::operator==(const Order &order) const {
    return this->orderType == order.orderType;
}

// OrderList methods
OrderList::OrderList()
{
    this->orders = new std::vector<Order>;
}

OrderList::OrderList(const OrderList *orderList)
{
    this->orders = new std::vector(*orderList->orders);
}

OrderList &OrderList::operator=(const OrderList &orderList)
{
    this->orders = new std::vector(*orderList.orders);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const OrderList &orderList)
{
    stream << "Order List[";
    int counter = 1;
    for (Order order: *orderList.orders){
        if (counter++ < orderList.orders->size())
            stream << order.getOrderType() << ",";
        else
            stream << order.getOrderType();
    }
    stream << "]";
    return stream;
}

void OrderList::add(Order *order)
{
    this->orders->push_back(order);
}

Order& OrderList::remove(int index)
{
    if (index > 0 && index < this->orders->size()){
        auto* order = new Order(*this->orders->erase(this->orders->begin() + index));
        return *order;
    } else
        throw std::runtime_error("Cannot remove order, index out of range");
}

void OrderList::move(Order *order, int newIndex, int oldIndex)
{
    if(newIndex < this->orders->size()) {
        this->orders->insert(this->orders->begin() + newIndex, order);
        this->orders->erase(this->orders->begin() + (oldIndex - 1));
    }
    else
        throw std::runtime_error("Invalid index");
}

std::vector<Order> OrderList::getOrders() {
    return *this->orders;
}

bool OrderList::operator==(const OrderList &orderList) const {
    return this->orders == orderList.orders;
}
