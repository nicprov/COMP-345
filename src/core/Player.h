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
    PlayerStrategy::StrategyType getStrategyType(); // get the strategy type
    void setStrategyType(PlayerStrategy::StrategyType); //set the strategy type
    OrderList& getOrderList(); //get the order list
    OrderList* getOrders(); //get the orders
    void attachExistingObservers(Subject*, const std::vector<Observer*>&); // attach the observers to the passed subject
    bool hasNegotiationWith(Player* enemy); // checks if players have negotiations with each-other
    void issueDeployOrders(Map*); // prompts player to issue deploy orders
    void issueAdvanceOrders(Map*, Deck*, std::vector<Player*>); // prompts player to issue advance orders
    Order* getCardOrderDetails(Card*, Map*, std::vector<Player*>&); // prompts player to create order from card
    Hand* hand;
    OrderList* orderList;
    PlayerStrategy* playerStrategy;
    int armyPool; //reinforcement pool
private:
    std::string name;
    Order* advance(Map*, Deck*);
};

void getValidatedInput(int&, int, int); // helper function to validate input while making a choice
