#include "Orders.h"
#include <string>
using namespace std;

Order::Order(){
    this->orderName = "";
}
Order::Order(string orderName){
    this->orderName = orderName;
}
Order::Order(Order *order) {
    this->orderName = order->orderName;
}

Order::Order(const Order &order)
{
    this->orderName = order.orderName;
}

void Order::operator=(const Order &order)
{
    this->orderName = order.orderName;
}

std::ostream& operator<< (std::ostream &stream, const Order &order)
{
    return stream << "Order(" << order.orderName << ")";
}

OrderList::OrderList(){
    //this->orderLists = new vector<Order>;
}

OrderList::OrderList(OrderList *orderlist) {
    this->orderLists = orderlist->orderLists;
}

OrderList::OrderList(const OrderList &orderlist)
{
    this->orderLists = orderlist.orderLists;
}

void OrderList::operator=(const OrderList &orderlist)
{
    orderLists = orderlist.orderLists;
}

std::ostream& operator<< (std::ostream &stream, const OrderList &orderlist)
{
    stream << "Order List[";
    int counter = 1;
    for (Order* order: orderlist.orderLists){
        if (counter++ < orderlist.orderLists.size())
            stream << order->orderName << ",";
        else
            stream << order->orderName;
    }
    stream << "]";
    return stream;
}

void OrderList::remove(vector<Order*> &list, int index) {
        list.erase(list.begin()+index);
}

void OrderList::move(vector<Order*> &list, Order order, int newIndex, int oldIndex) {
    if(newIndex < list.size()) {
        list.insert(list.begin() + newIndex, &order);
        list.erase(list.begin() + (oldIndex - 1));
    }
    else{
        cout << "invalid index" << endl;
    }
}