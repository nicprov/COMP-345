#ifndef TEST1_CARDS_H
#define TEST1_CARDS_H
#include <vector>

class Card
{
public:
    enum Card_Type
    {
        bomb,
        reinforcement,
        blockage,
        airlift,
        diplomacy
    };
    Card(Card_Type&);
    // Copy constructor
    Card(const Card&);
    // Assignment operator
    void operator= (Const Card&);
    // Stream output operator
    friend std:ostream& operator<< (std:ostream&, const Card&);
    void play();
private:
    Card_Type type;
};

class Hand
{
public:
    Hand();
    // Copy constructor
    Hand(Const Hand&);
    // Assignment operator
    void operator= (Const Card&);
    // Stream output operator
    friend std:ostream& operator<< (std:ostream&, const Hand&);
    void addCard();
    void removeCard();
private:
    std::vector<Card> cards;
};

class Deck{
public:
    Deck();
    // Copy constructor
    Deck(Const Deck&);
    // Assignment operator
    void operator= (Const Deck&);
    // Stream output operator
    friend std:ostream& operator<< (std:ostream&, const Deck&);
    void draw();
    void addCard();
    void removeCard();
private:
    std::vector<Card> cards;

};
#endif //TEST1_CARDS_H
