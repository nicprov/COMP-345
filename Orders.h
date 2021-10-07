#include <iostream>  // for cin,cout,fixed,showpoint,setw()
#include <string>    // for to_string()
#include <list>
using namespace std;

class Order{
    public:
        Order();
        Order(const Order&);
        void operator = (Const Order&);
        string orderEffect;
        string orderName;
        void output();
        friend ostream &operator<<( ostream &output, const Order &O )
}

class deploy: public Order{
    public:
        void executed();
        void validate();
}

class advance: public Order{
    public:
        void executed();
        void validate();
}

class bomb: public Order{
    public:
        void executed();
        void validate();    
}

class blockade: public Order{
    public:
        void executed();
        void validate();    
}

class airlift: public Order{
    public:
        void executed();
        void validate();  
}

class negotiate: public Order{
    public:
        void executed();
        void validate();    
}

class OrderList{
    
    public:
        OrderList();
        OrderList(const OrderList&);
        void operator = (const OrderList&);
        void remove(Order toRemove);
        void move(Order moved);
        friend ostream &operator<<( ostream &output, const OrderList &OL )
    private:
        list<Order> orderLists;


}