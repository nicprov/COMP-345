#include <iostream>
#include "Orders.h"
using namespace std;

void ordersDriver() {

    OrderList list = OrderList();
    DeployOrder deploy;
    deploy.Order::orderName = "deploy";
    list.orderLists.push_back(&deploy);
    cout << deploy << endl;
    cout << list << endl;
    AdvanceOrder advance;
    advance.Order::orderName = "advance";
    list.orderLists.push_back(&advance);
    cout << advance << endl;
    cout << list << endl;
    BombOrder bomb;
    bomb.Order::orderName = "bomb";
    list.orderLists.push_back(&bomb);
    cout << bomb << endl;
    cout <<  list << endl;
    BlockadeOrder blockade;
    blockade.Order::orderName = "blockade";
    list.orderLists.push_back(&blockade);
    cout << blockade << endl;
    cout <<  list << endl;
    AirliftOrder airlift;
    airlift.Order::orderName = "airlift";
    list.orderLists.push_back(&airlift);
    cout << airlift << endl;
    cout << list << endl;
    NegotiateOrder negotiate;
    negotiate.Order::orderName = "negotiate";
    list.orderLists.push_back(&negotiate);
    cout <<  negotiate << endl;
    cout << list << endl;

    list.remove(list.orderLists, 1);
    cout <<  list << endl;
    list.move(list.orderLists, bomb, 4, 2);
    cout <<  list << endl;
}