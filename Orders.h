#include <iostream>  
#include <string>    
#include <vector>
using namespace std;

class Order{
    public:
        Order();
        Order(string orderName);
        Order(Order*);;
        Order(const Order&);
        void operator = (const Order&);
        friend ostream& operator<< (ostream&, const Order&);
        string orderName;
};

class DeployOrder: public Order{
    public:
        void execute();
        void validate();
};

class AdvanceOrder: public Order{
    public:
        void execute();
        void validate();
};

class BombOrder: public Order{
    public:
        void execute();
        void validate();    
};

class BlockadeOrder: public Order{
    public:
        void execute();
        void validate();    
};

class AirliftOrder: public Order{
    public:
        void execute();
        void validate();  
};

class NegotiateOrder: public Order{
    public:
        void execute();
        void validate();    
};

class OrderList{
    
    public:
        OrderList();
        OrderList(OrderList*);;
        OrderList(const OrderList&);
        void operator = (const OrderList&);
        friend ostream& operator<< (ostream&, const OrderList&);
        void remove(vector<Order*>&, int);
        void move(vector<Order*>& list, Order order, int newIndex, int oldIndex);
        vector<Order*> orderLists;


};