#pragma once    //include guard

#include <vector>
#include <string>
#include "PlayerStrategies.h"

//class forward reference
class Order;
class OrderList;
class Hand;
class Territory;
class Map;
class Deck;
class Card;
class Subject;
class Observer;

//Player class and function declarations
class Player
{
public:
    ~Player(); //Destructor
    Player(); //Default constructor
    Player(const std::string&, PlayerStrategy::StrategyType); //Default constructor
    Player(PlayerStrategy::StrategyType, const Hand&, const OrderList&, const std::string&); //Player constructor
    Player(const Player&);// Copy constructor
    Player& operator= (const Player&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Player&); // Stream output operator
    bool operator== (const Player&) const; // Comparison of player
    std::vector<Territory*> toDefend(Map*); // Territories to Defend
    std::vector<Territory*> toAttack(Map*); // Territories to Attack
    void issueOrder(Deck*, Map*, std::vector<Player*>&); // Adds order to order list
    std::string& getName(); //get name of player
    PlayerStrategy::StrategyType getStrategyType();
    void setStrategyType(PlayerStrategy::StrategyType);
    OrderList& getOrderList(); //get the order list
    OrderList* getOrders(); //get the orders
    void attachExistingObservers(Subject*, const std::vector<Observer*>&);
    bool hasNegotiationWith(Player* enemy); // checks if players have negotiations with each-other
    void issueDeployOrders(Map*);
    void issueAdvanceOrders(Map*, Deck*, std::vector<Player*>);
    Order* getCardOrderDetails(Card*, Map*, std::vector<Player*>&);
    Hand* hand;
    OrderList* orderList;
    int armyPool; //reinforcement pool
private:
    PlayerStrategy* playerStrategy;
    std::string name;
    Order* advance(Map*, Deck*);
};

void getValidatedInput(int&, int, int);
