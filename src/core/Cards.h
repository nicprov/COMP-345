#pragma once

#include <vector>
#include <iosfwd>
#include "Orders.h"
#include "Player.h"

//class forward reference
class Hand;
class Deck;
class OrderList;
class Player;
class Map;

//Card class and function declarations
class Card
{
public:
    // CardType enum. list of cards
    enum CardType
    {
        bomb = 1,
        reinforcement = 2,
        blockade = 3,
        airlift = 4,
        diplomacy = 5
    };
    Card(CardType); //Card constructor
    Card(const Card&); // Copy constructor
    Card& operator= (const Card&); // Assignment operator
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Card&);
    friend std::ostream& operator<< (std::ostream&, const CardType&);
    bool operator== (const Card&) const; //Comparison of player
    void play(Deck*, Player*, Order*); //Play card
    CardType& getType();    //get card type
    void attachExistingObservers(Subject*, const std::vector<Observer*>&);
    static constexpr std::initializer_list<CardType> ALL_Card_Type = { bomb, reinforcement, blockade, airlift, diplomacy }; //initialize card type
private:
    CardType* type;
};

//Hand class and function declarations
class Hand
{
public:
    ~Hand();    //Destructor
    Hand();     // Hand Constructor
    Hand(const Hand&);  // Copy constructor
    Hand& operator= (const Hand&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Hand&); // Stream output operator
    bool operator== (const Hand&) const;    //Compare cards
    void addCard(Card*);   //add Card to hand
    void removeCard(Card*); //remove card from hand
    std::vector<Card*> getCards();  //vector of cards
private:
    std::vector<Card*> cards;
};

//Deck class and function declarations
class Deck {
public:
    ~Deck();    //Destructor
    Deck();     //Deck Constructor
    Deck(const Deck&); // Copy constructor
    Deck& operator= (const Deck&); // Assignment operator
    friend std::ostream& operator<< (std::ostream&, const Deck&); // Stream output operator
    bool operator== (const Deck&) const; //Compare Deck
    Card* draw();   //draw a card
    void returnCard(Card*); //return card
    void setCards(std::vector<Card*>&); // Set cards
    std::vector<Card*> getCards();  // Get cards
    static constexpr int NUM_CARDS_PER_TYPE = 10; //constant number of cards per type
private:
    std::vector<Card*> cards;
};