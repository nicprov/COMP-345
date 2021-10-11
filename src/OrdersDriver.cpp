#include <iostream>
#include "Orders.h"

void ordersDriver() {

    // Add all order types
    OrderList orderList = OrderList();
    Order deploy = Deploy(Order::OrderType::deploy);
    Order advance = Advance(Order::OrderType::advance);
    Order bomb = Bomb(Order::OrderType::bomb);
    Order blockade = Blockade(Order::OrderType::blockade);
    Order airlift = Airlift(Order::OrderType::airlift);
    Order negotiate = Negotiate(Order::OrderType::negotiate);
    orderList.add(&deploy);
    orderList.add(&advance);
    orderList.add(&bomb);
    orderList.add(&blockade);
    orderList.add(&airlift);
    orderList.add(&negotiate);

    // Show orders
    cout << orderList << endl;

    // Execute all orders
    cout << endl;
    deploy.execute();
    cout << " | ";
    deploy.validate();
    cout << endl;
    advance.execute();
    cout << " | ";
    advance.validate();
    cout << endl;
    bomb.execute();
    cout << " | ";
    bomb.validate();
    cout << endl;
    blockade.execute();
    cout << " | ";
    blockade.validate();
    cout << endl;
    airlift.execute();
    cout << " | ";
    airlift.validate();
    cout << endl;
    negotiate.execute();
    cout << " | ";
    negotiate.validate();
    cout << endl << endl;

    // Remove order
    cout <<  "Removing order: " << orderList.remove(1) << endl;

    // Move order
    orderList.move(&airlift, 1, 4);
}