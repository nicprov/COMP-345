#include <iostream>
#include "../core/Orders.h"
#include "../core/LoggingObserver.h"

using std::cout;
using std::endl;

void ordersDriver() {

    // Add all order types
    OrderList orderList = OrderList();
    LogObserver* oList = new LogObserver(&orderList);
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
    LogObserver* ODeploy = new LogObserver(deploy);
    LogObserver* OAdvance = new LogObserver(advance);
    LogObserver* OBomb = new LogObserver(bomb);
    LogObserver* OBlockade = new LogObserver(blockade);
    LogObserver* OAirlift = new LogObserver(airlift);
    LogObserver* ONegotiate = new LogObserver(negotiate);



    // Show orders
    cout << orderList << endl;

    // Validate then execute all orders
    cout << endl;
    if (deploy->validate())
        deploy->execute();
    cout << endl;
    deploy->Detach(ODeploy);

    if (advance->validate())
        advance->execute();
    cout << endl;
    advance->Detach(OAdvance);

    if (bomb->validate())
        bomb->execute();
    cout << endl;
    bomb->Detach(OBomb);

    if (blockade->validate())
        blockade->execute();
    cout << endl;
    blockade->Detach(OBlockade);

    if (airlift->validate())
        airlift->execute();
    cout << endl;
    airlift->Detach(OAirlift);

    if (negotiate->validate())
        negotiate->execute();
    cout << endl << endl;
    negotiate->Detach(ONegotiate);

    // Remove order
    orderList.remove(1);

    // Move order
    orderList.move(airlift, 1, 3);

    //Show orderList again after changes
    cout << orderList;

}