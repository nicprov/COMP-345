#include <iostream>  
#include <string>    
#include <vector>

class Order{
public:
    enum OrderType{
        deploy=1,
        advance=2,
        bomb=3,
        blockade=4,
        airlift=5,
        negotiate=6
    };
    Order(const OrderType);
    Order(const Order*); // Copy constructor
    Order& operator= (const Order&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Order&); // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const OrderType&); // Stream output operator
    bool operator== (const Order&) const;
    OrderType& getOrderType();
    virtual void execute();
    virtual bool validate();
    static constexpr std::initializer_list<OrderType> ALL_ORDER_TYPES = {deploy, advance, bomb, blockade, airlift, negotiate};
private:
    OrderType* orderType;
};

class Deploy: public Order {
public:
    Deploy(const OrderType);
    void execute();
    bool validate();
};

class Advance: public Order {
public:
    Advance(const OrderType);
    void execute();
    bool validate();
};

class Bomb: public Order {
public:
    Bomb(const OrderType);
    void execute();
    bool validate();
};

class Blockade: public Order {
public:
    Blockade(const OrderType);
    void execute();
    bool validate();
};

class Airlift: public Order {
public:
    Airlift(const OrderType);
    void execute();
    bool validate();
};

class Negotiate: public Order {
public:
    Negotiate(const OrderType);
    void execute();
    bool validate();
};

class OrderList{
public:
    OrderList();
    OrderList(const OrderList*); // Copy constructor
    OrderList& operator = (const OrderList&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const OrderList&); // Stream output operator
    bool operator== (const OrderList&) const;
    void add(Order*);
    Order& remove(int);
    void move(Order*, int newIndex, int oldIndex);
    std::vector<Order> getOrders();
private:
    std::vector<Order>* orders;
};