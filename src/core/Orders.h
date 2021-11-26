#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include "LoggingObserver.h"

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
    bool operator== (const Order&) const; //equals operator
    OrderType& getOrderType(); //accessor for OrderType
    virtual void execute() = 0; //execute order method, virtual to avoid ambiguity with subclass methods
    virtual bool validate() = 0; //validate order method, virtual to avoid ambiguity with subclass methods
    std::string stringToLog();
    static constexpr std::initializer_list<OrderType> ALL_ORDER_TYPES = { deploy, advance, bomb, blockade, airlift, negotiate };
    static const boost::unordered_map<OrderType, std::string> orderTypeMapping;
protected:
    OrderType* orderType; //pointer to ordertype of order
};

class Deploy : public Order {
public:
    ~Deploy();
    Deploy(Player*, Territory*, int); //parameterized constructor
    Deploy(const Deploy&); //copy constructor
    Deploy& operator= (const Deploy&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Deploy&); // Stream output operator
    void execute(); //execute method for deploy orders
    bool validate(); //validate method for deploy orders
private:
    Player* player; //pointer to the player of the order
    Territory* territory; //pointer to the territory to deploy to
    int numOfArmies; //integer number of armies
};

class Advance : public Order {
public:
    ~Advance();
    Advance(Deck*, Player*, Territory*, Territory*, int); //parameterized constructor
    Advance(const Advance&); //copy constructor
    Advance& operator= (const Advance&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Advance&); // Stream output operator
    void execute(); //execute method for advance orders
    bool validate(); //validate method for advance orders
private:
    Deck* deck; //pointer to the deck
    Player* player; //pointer to the player of the order
    Territory* source; //pointer to source territory
    Territory* target; //pointer to target territory
    int numOfArmies; //integer number of armies
};

class Bomb : public Order {
public:
    ~Bomb();
    Bomb(Player*, Territory*); //parameterized constructor
    Bomb(const Bomb&); //copy constructor
    Bomb& operator= (const Bomb&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Bomb&); // Stream output operator
    void execute(); //execute method for bomb orders
    bool validate(); //validate method for bomb methods
private:
    Player* player; //pointer to the player of the order
    Territory* target; //pointer to target territory
};

class Blockade : public Order {
public:
    ~Blockade();
    Blockade(Player*, Territory*, std::vector<Player*>& players); //parameterized constructor
    Blockade(const Blockade&); //copy constructors
    Blockade& operator= (const Blockade&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Blockade&); // Stream output operator
    void execute(); //execute method for blockade order
    bool validate(); //execute method for validate order
private:
    Territory* target; //pointer to target territory
    Player* player; //pointer to the player of the order
    std::vector<Player*> players;
};

class Airlift : public Order {
public:
    ~Airlift();
    Airlift(Player*, Territory*, Territory*, int); //parameterized constructor
    Airlift(const Airlift&); //copy constructor
    Airlift& operator= (const Airlift&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Airlift&); // Stream output operator
    void execute(); //execute method for airlift order
    bool validate(); //valid method for airlift order
private:
    Player* player; //pointer to the player of the order
    Territory* source; //pointer to source territory
    Territory* target; //pointer to target territory
    int numOfArmies; //integer number of armies
};

class Negotiate : public Order {
public:
    ~Negotiate();
    Negotiate(Player*, Player*);  //parameterized constructor
    Negotiate(const Negotiate&); //copy constructor
    Negotiate& operator= (const Negotiate&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Negotiate&); // Stream output operator
    void execute(); //execute method for negotiate order
    bool validate(); //validate method for negotiate order
    Player* getEnemy(); //get enemy
private:
    Player* player; //pointer to the player of the order
    Player* enemy; //pointer to the enemy player
};

class OrderList: public Subject {
public:
    ~OrderList(); //destructor
    OrderList(); //default constructor
    OrderList(const OrderList&); // Copy constructor
    OrderList& operator = (const OrderList&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const OrderList&); // Stream output operator
    bool operator== (const OrderList&) const; //equals operator
    void add(Order*); //add method to append a new Order pointer to list
    void remove(int); //remove method to remove an Order from an index
    void move(Order*, int newIndex, int oldIndex); //move method to move a specific order from one index to another
    std::vector<Order*> getOrders(); //accessor method for order list
    int getSize();
    std::string stringToLog();
private:
    std::vector<Order*> orders; //pointer to list of order pointers
};