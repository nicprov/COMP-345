#include <iostream>
#include "../core/Orders.h"

using std::cout;
using std::endl;

void ordersDriver() {

    // Add all order types
    OrderList orderList = OrderList();
    Order* deploy = new Deploy(Order::OrderType::deploy);
    Order* advance = new Advance(Order::OrderType::advance);
    Order* bomb = new Bomb(Order::OrderType::bomb);
    Order* blockade = new Blockade(Order::OrderType::blockade);
    Order* airlift = new Airlift(Order::OrderType::airlift);
    Order* negotiate = new Negotiate(Order::OrderType::negotiate);
    orderList.add(deploy);
    orderList.add(advance);
    orderList.add(bomb);
    orderList.add(blockade);
    orderList.add(airlift);
    orderList.add(negotiate);

    // Show orders
    cout << orderList << endl;

    // Validate then execute all orders
    cout << endl;
    if (deploy->validate())
        deploy->execute();
    cout << endl;
    if (advance->validate())
        advance->execute();
    cout << endl;
    if (bomb->validate())
        bomb->execute();
    cout << endl;
    if (blockade->validate())
        blockade->execute();
    cout << endl;
    if (airlift->validate())
        airlift->execute();
    cout << endl;
    if (negotiate->validate())
        negotiate->execute();
    cout << endl << endl;

    // Remove order
    orderList.remove(1);

    // Move order
    orderList.move(airlift, 1, 3);

    //Show orderList again after changes
    cout << orderList;
}