#pragma once

#include <iostream>
#include <string>
#include <vector>

//To use the territory and player classes
#include "Map.h"
#include "Player.h"
#include "Cards.h"

class Player;
class Territory;
class Deck;

class Order {
public:
    enum OrderType {
        deploy = 1,
        advance = 2,
        bomb = 3,
        blockade = 4,
        airlift = 5,
        negotiate = 6
    };
    Order(const OrderType);
    Order(const OrderType orderType, Player* player); //Parameterized constructor
    Order(const OrderType orderType, Player* player, Deck& deck);
    Order(const Order&); // Copy constructor
    Order& operator= (const Order&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Order&); // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const OrderType&); // Stream output operator
    bool operator== (const Order&) const;
    OrderType& getOrderType();
    const Player* getPlayer();
    void setPlayer(Player* player);
    virtual void execute();
    virtual bool validate();
    static constexpr std::initializer_list<OrderType> ALL_ORDER_TYPES = { deploy, advance, bomb, blockade, airlift, negotiate };
protected:
    OrderType* orderType; //pointer to ordertype of order
    Player* player; //pointer to the player of the order

};

class Deploy : public Order {
public:
    ~Deploy();
    Deploy(const OrderType orderType);
    Deploy(const OrderType orderType, Player* player, Territory* territory, int numOfArmies); //parameterized constructor
    Deploy(const Deploy&); //copy constructor
    Deploy& operator= (const Deploy&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Deploy&); // Stream output operator
    void execute(); //execute method for deploy orders
    bool validate(); //validate method for deploy orders
private:
    Territory* territory;
    int numOfArmies;
};

class Advance : public Order {
public:
    ~Advance();
    Advance(const OrderType orderType);
    Advance(const OrderType orderType, Player* player, Territory* source, Territory* target, int numOfArmies); //parameterized constructor
    Advance(const Advance&); //copy constructor
    Advance& operator= (const Advance&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Advance&); // Stream output operator
    void execute(Deck& deck); //execute method for advance orders
    bool validate(); //validate method for advance orders
private:
    Territory* source;
    Territory* target;
    int numOfArmies;
};

class Bomb : public Order {
public:
    ~Bomb();
    Bomb(const OrderType orderType);
    Bomb(const OrderType orderType, Player* player, Territory* target); //parameterized constructor
    Bomb(const Bomb&); //copy constructor
    Bomb& operator= (const Bomb&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Bomb&); // Stream output operator
    void execute(); //execute method for bomb orders
    bool validate(); //validate method for bomb methods
private:
    Territory* target;
};

class Blockade : public Order {
public:
    ~Blockade();
    Blockade(const OrderType orderType);
    Blockade(const OrderType, Player* player, Territory* target); //parameterized constructor
    Blockade(const Blockade&); //copy constructors
    Blockade& operator= (const Blockade&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Blockade&); // Stream output operator
    void execute(); //execute method for blockade order
    bool validate(); //execute method for validate order
private:
    Territory* target;
};

class Airlift : public Order {
public:
    ~Airlift();
    Airlift(const OrderType orderType);
    Airlift(const OrderType orderType, Player* player, Territory* source, Territory* target, int numOfArmies); //parameterized constructor
    Airlift(const Airlift&); //copy constructor
    Airlift& operator= (const Airlift&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Airlift&); // Stream output operator
    void execute(); //execute method for airlift order
    bool validate(); //valid method for airlift order
private:
    Territory* source;
    Territory* target;
    int numOfArmies;
};

class Negotiate : public Order {
public:
    ~Negotiate();
    Negotiate(const OrderType orderType);
    Negotiate(const OrderType orderType, Player* current, Player* enemy);  //parameterized constructor
    Negotiate(const Negotiate&); //copy constructor
    Negotiate& operator= (const Negotiate&); //assignment operator
    friend std::ostream& operator<< (std::ostream&, const Negotiate&); // Stream output operator
    void execute(); //execute method for negotiate order
    bool validate(); //validate method for negotiate order
    Player* getEnemy(); //get enemy
private:
    Player* enemy;
};

class OrderList {
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
private:
    std::vector<Order*>* orders;
};