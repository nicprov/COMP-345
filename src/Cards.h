#ifndef TEST1_CARDS_H
#define TEST1_CARDS_H
#include <vector>
#include <iosfwd>
#include "Orders.h"

class Hand;
class Deck;

class Card
{
public:
    enum CardType
    {
        bomb=1,
        reinforcement=2,
        blockade=3,
        airlift=4,
        diplomacy=5
    };
    Card(CardType);
    // Copy constructor
    Card(const Card*);
    // Assignment operator
    Card& operator= (const Card&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Card&);
    friend std::ostream& operator<< (std::ostream&, const CardType&);
    bool operator== (const Card&) const;
    void play(OrderList*, Hand*, Deck*);
    CardType& getType();
    static constexpr std::initializer_list<CardType> ALL_Card_Type = {bomb, reinforcement, blockade, airlift, diplomacy};
private:
    CardType *type;
};

class Hand
{
public:
    ~Hand();
    Hand();
    // Copy constructor
    Hand(const Hand*);
    // Assignment operator
    Hand& operator= (const Hand&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Hand*);
    bool operator== (const Hand&) const;
    void addCard(Card*);
    void removeCard(Card*);
    std::vector<Card*> getCards();
private:
    std::vector<Card*> *cards;
};

class Deck{
public:
    ~Deck();
    Deck();
    // Copy constructor
    Deck(const Deck*);
    // Assignment operator
    Deck& operator= (const Deck&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const Deck*);
    bool operator== (const Deck&) const;
    Card* draw();
    void returnCard(Card*);
    std::vector<Card*> getCards();
    static constexpr int NUM_CARDS_PER_TYPE = 10;
private:
    std::vector<Card*> *cards;
};
#endif //TEST1_CARDS_H
