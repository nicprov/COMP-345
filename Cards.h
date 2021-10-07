#ifndef TEST1_CARDS_H
#define TEST1_CARDS_H
#include <vector>
#include <iosfwd>
using namespace std;

class Card
{
public:
    enum Card_Type
    {
        bomb=1,
        reinforcement=2,
        blockade=3,
        airlift=4,
        diplomacy=5
    };
    Card(Card_Type);
    Card(Card*);
    // Copy constructor
    Card(const Card&);
    // Assignment operator
    void operator= (const Card&);
    // Stream output operator
    friend ostream& operator<< (ostream&, const Card&);
    friend ostream& operator<< (ostream&, const Card_Type&);
    void play();
    Card_Type& getType();
    static constexpr initializer_list<Card_Type> ALL_Card_Type = {bomb, reinforcement, blockade, airlift, diplomacy};
private:
    Card_Type type;
};

class Hand
{
public:
    Hand();
    // Copy constructor
    Hand(const Hand&);
    // Assignment operator
    void operator= (const Hand&);
    // Stream output operator
    friend ostream& operator<< (std::ostream&, const Hand&);
    void addCard(Card&);
    void removeCard(Card&);
private:
    vector<Card> *cards;
};

class Deck{
public:
    Deck();
    // Copy constructor
    Deck(const Deck&);
    // Assignment operator
    void operator= (const Deck&);
    // Stream output operator
    friend ostream& operator<< (ostream&, const Deck&);
    Card& draw();
    static constexpr int NUM_CARDS_PER_TYPE = 10;
private:
    vector<Card> *cards;
};
#endif //TEST1_CARDS_H
