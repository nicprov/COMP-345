#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"

//To use the territory and player classes
#include "Map.h"
#include "Player.h"
#include "Cards.h"


class Order: public Subject{

class Player;
class Territory;
class Deck;
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

    bool operator== (const Order&) const; //equals operator
    OrderType& getOrderType(); //accessor for OrderType
    virtual void execute() = 0; //execute order method, virtual to avoid ambiguity with subclass methods
    virtual bool validate() = 0; //validate order method, irtual to avoid ambiguity with subclass methods
    static constexpr std::initializer_list<OrderType> ALL_ORDER_TYPES = {deploy, advance, bomb, blockade, airlift, negotiate}; //array of const OrderType with 1 of each type
    virtual std::string stringToLog() =0;
protected:
    OrderType* orderType; //pointer to ordertype of order
};

class Deploy : public Order {
public:
    ~Deploy();
    Deploy(OrderType);
    Deploy(OrderType, Player*, Territory*, int); //parameterized constructor
    Deploy(const Deploy&); //copy constructor
    Deploy& operator= (const Deploy&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Deploy&); // Stream output operator

    void execute(Player&); //execute method for deploy orders
    bool validate(Player&); //validate method for deploy orders
    std::string stringToLog();
private:
    Territory* territory;
    int numOfArmies;
};

class Advance : public Order {
public:
    ~Advance();
    Advance(OrderType);
    Advance(OrderType, Territory*, Territory*, int); //parameterized constructor
    Advance(const Advance&); //copy constructor
    Advance& operator= (const Advance&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Advance&); // Stream output operator

    void execute(Deck&, Player&); //execute method for advance orders
    bool validate(Player&); //validate method for advance orders
    std::string stringToLog();
private:
    Territory* source;
    Territory* target;
    int numOfArmies;
};

class Bomb : public Order {
public:
    ~Bomb();
    Bomb(OrderType);
    Bomb(OrderType, Territory*); //parameterized constructor
    Bomb(const Bomb&); //copy constructor
    Bomb& operator= (const Bomb&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Bomb&); // Stream output operator

    void execute(Player&); //execute method for bomb orders
    bool validate(Player&); //validate method for bomb methods
    std::string stringToLog();
private:
    Territory* target;

};

class Blockade : public Order {
public:
    ~Blockade();
    Blockade(OrderType);
    Blockade(OrderType, Territory*); //parameterized constructor
    Blockade(const Blockade&); //copy constructors
    Blockade& operator= (const Blockade&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Blockade&); // Stream output operator
    void execute(Player&); //execute method for blockade order
    bool validate(Player&); //execute method for validate order
    std::string stringToLog();

private:
    Territory* target;

};

class Airlift : public Order {
public:
    ~Airlift();
    Airlift(OrderType);
    Airlift(OrderType, Territory*, Territory*, int); //parameterized constructor
    Airlift(const Airlift&); //copy constructor
    Airlift& operator= (const Airlift&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Airlift&); // Stream output operator
    void execute(Player&); //execute method for airlift order
    bool validate(Player&); //valid method for airlift order
    std::string stringToLog();

private:
    Territory* source;
    Territory* target;

};

class Negotiate : public Order {
public:
    ~Negotiate();
    Negotiate(OrderType);
    Negotiate(OrderType, Player*);  //parameterized constructor
    Negotiate(const Negotiate&); //copy constructor
    Negotiate& operator= (const Negotiate&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Negotiate&); // Stream output operator
    std::string stringToLog();
    void execute(Player&); //execute method for negotiate order
    bool validate(Player&); //validate method for negotiate order
    Player* getEnemy(); //get enemy
private:
    Player* enemy;
};

//Order List class:
// used to create a list of all user Orders and allow them to be moved around or deleted
class OrderList : public Subject{
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