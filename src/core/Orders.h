//make sure that all files are only defined once
#pragma once

//this class uses streams and vectors
#include <iostream>
#include <vector>

// Order Class:
// used to define orders given by players during their turn,
// each order has an ordertype which is on of the 6 valid orders in warzone

class Order{
public:
    //valid Order Types
    enum OrderType{
        deploy=1,
        advance=2,
        bomb=3,
        blockade=4,
        airlift=5,
        negotiate=6
    };
    virtual ~Order();
    Order(const OrderType); //Parameterized constructor
    Order(const Order&); // Copy constructor
    Order& operator= (const Order&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Order&); // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const OrderType&); // Stream output operator
    bool operator== (const Order&) const; //equals operator
    OrderType& getOrderType(); //accessor for OrderType
    virtual void execute() = 0; //execute order method, virtual to avoid ambiguity with subclass methods
    virtual bool validate() = 0; //validate order method, irtual to avoid ambiguity with subclass methods
    static constexpr std::initializer_list<OrderType> ALL_ORDER_TYPES = {deploy, advance, bomb, blockade, airlift, negotiate}; //array of const OrderType with 1 of each type
protected:
    OrderType* orderType; //pointer to ordertype of order
};

//subclass of order for deploy Orders
class Deploy: public Order {
public:
    ~Deploy();
    Deploy(const OrderType); //parameterized constructor
    Deploy(const Deploy&); //copy constructor
    Deploy& operator= (const Deploy&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Deploy&); // Stream output operator
    void execute(); //execute method for deploy orders
    bool validate(); //validate method for deploy orders
};

//subclass of order for advance Orders
class Advance: public Order {
public:
    ~Advance();
    Advance(const OrderType); //parameterized constructor
    Advance(const Advance&); //copy constructor
    Advance& operator= (const Advance&); //assignement operator
    friend std::ostream& operator<< (std::ostream&, const Advance&); // Stream output operator
    void execute(); //execute method for advance orders
    bool validate(); //validate method for advance orders
};

//subclass of order for bomb Orders
class Bomb: public Order {
public:
    ~Bomb();
    Bomb(const OrderType); //parameterized constructor
    Bomb(const Bomb&); //copy constructor
    Bomb& operator= (const Bomb&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Bomb&); // Stream output operator
    void execute(); //execute method for bomb orders
    bool validate(); //validate method for bomb methods
};

//subclass of order for blockade Orders
class Blockade: public Order {
public:
    ~Blockade();
    Blockade(const OrderType); //parameterized constructor
    Blockade(const Blockade&); //copy constructors
    Blockade& operator= (const Blockade&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Blockade&); // Stream output operator
    void execute(); //execute method for blockade order
    bool validate(); //execute method for validate order
};

//subclass of order for airlift Orders
class Airlift: public Order {
public:
    ~Airlift();
    Airlift(const OrderType); // parameterized constructor
    Airlift(const Airlift&); //copy constructor
    Airlift& operator= (const Airlift&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Airlift&); // Stream output operator
    void execute(); //execute method for airlift order
    bool validate(); //valid method for airlift order
};

//subclass of order for negotiate Orders
class Negotiate: public Order {
public:
    ~Negotiate();
    Negotiate(const OrderType);  //parameterized constructor
    Negotiate(const Negotiate&); //copy constructor
    Negotiate& operator= (const Negotiate&); //assignemnt operator
    friend std::ostream& operator<< (std::ostream&, const Negotiate&); // Stream output operator
    void execute(); //execute method for negotiate order
    bool validate(); //validate method for negotiate order
};

//Order List class:
// used to create a list of all user Orders and allow them to be moved around or deleted
class OrderList{
public:
    ~OrderList(); //destructor
    OrderList();//default constructor
    OrderList(const OrderList&); // Copy constructor
    OrderList& operator = (const OrderList&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const OrderList&); // Stream output operator
    bool operator== (const OrderList&) const; //equals operator
    void add(Order*); //add method to append a new Order pointer to list
    void remove(int); //remove method to remove an Order from an index
    void move(Order*, int newIndex, int oldIndex); //move method to move a specific order from one index to another
    std::vector<Order*> getOrders(); //accessor method for order list
    int getSize();
private:
    std::vector<Order*>* orders; //pointer to list of order pointers
};