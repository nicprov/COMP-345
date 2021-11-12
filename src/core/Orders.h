#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

class Player;
class Territory;
class Deck;

class Order: public Subject {
public:
    enum OrderType {
        deploy = 1,
        advance = 2,
        bomb = 3,
        blockade = 4,
        airlift = 5,
        negotiate = 6
    };
    Order(OrderType); //Parameterized constructor
    Order(const Order&); // Copy constructor
    Order& operator= (const Order&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Order&); // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const OrderType&); // Stream output operator
    bool operator== (const Order&) const;
    OrderType& getOrderType();
    virtual void execute();
    virtual bool validate();
    virtual std::string stringToLog() =0;
    static constexpr std::initializer_list<OrderType> ALL_ORDER_TYPES = { deploy, advance, bomb, blockade, airlift, negotiate };
protected:
    OrderType* orderType; //pointer to ordertype of order
};

class Deploy : public Order {
public:
    ~Deploy();
    Deploy(OrderType); //parameterized constructor
    Deploy(const Deploy&); //copy constructor
    Deploy& operator= (const Deploy&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Deploy&); // Stream output operator
    void execute(Player&, Territory&, int); //execute method for deploy orders
    bool validate(Player&, Territory&, int); //validate method for deploy orders
    std::string stringToLog();
};

class Advance : public Order {
public:
    ~Advance();
    Advance(OrderType); //parameterized constructor
    Advance(const Advance&); //copy constructor
    Advance& operator= (const Advance&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Advance&); // Stream output operator
    void execute(Deck&, Player&, Territory&, Territory&, int); //execute method for advance orders
    bool validate(Player&, Territory&, Territory&); //validate method for advance orders
    std::string stringToLog();
};

class Bomb : public Order {
public:
    ~Bomb();
    Bomb(OrderType); //parameterized constructor
    Bomb(const Bomb&); //copy constructor
    Bomb& operator= (const Bomb&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Bomb&); // Stream output operator
    void execute(Player&, Territory&); //execute method for bomb orders
    bool validate(Player&, Territory&); //validate method for bomb methods
    std::string stringToLog();
};

class Blockade : public Order {
public:
    ~Blockade();
    Blockade(OrderType); //parameterized constructor
    Blockade(const Blockade&); //copy constructors
    Blockade& operator= (const Blockade&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Blockade&); // Stream output operator
    void execute(Player&, Territory&); //execute method for blockade order
    bool validate(Player&, Territory&); //execute method for validate order
    std::string stringToLog();
};

class Airlift : public Order {
public:
    ~Airlift();
    Airlift(OrderType); //parameterized constructor
    Airlift(const Airlift&); //copy constructor
    Airlift& operator= (const Airlift&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Airlift&); // Stream output operator
    void execute(Player&, Territory&, Territory&, int); //execute method for airlift order
    bool validate(Player&, Territory&, Territory&); //valid method for airlift order
    std::string stringToLog();
};

class Negotiate : public Order {
public:
    ~Negotiate();
    Negotiate(OrderType);  //parameterized constructor
    Negotiate(const Negotiate&); //copy constructor
    Negotiate& operator= (const Negotiate&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Negotiate&); // Stream output operator
    void execute(Player&, Player&); //execute method for negotiate order
    bool validate(Player&, Player&); //validate method for negotiate order
    std::string stringToLog();
};

class OrderList: public Subject {
public:
    ~OrderList();
    OrderList();
    OrderList(const OrderList&); // Copy constructor
    OrderList& operator = (const OrderList&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const OrderList&); // Stream output operator
    bool operator== (const OrderList&) const;
    void add(Order*);
    void remove(int);
    void move(Order*, int newIndex, int oldIndex);
    std::vector<Order*> getOrders();
    int getSize();
    std::string stringToLog();
private:
    std::vector<Order*>* orders;
};