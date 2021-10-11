#include <iostream>
#include "Orders.h"
using namespace std;

void ordersDriver() {

    // Add all order types
    OrderList orderList = OrderList();
    for (Order::OrderType orderType: Order::ALL_ORDER_TYPES){
        cout << "Adding order: " << static_cast<Order::OrderType>(orderType) << endl;
        Order order = Order(orderType);
        orderList.add(&order);
    }

    // Remove order
    cout <<  "Removing order: " << orderList.remove(1) << endl;
}