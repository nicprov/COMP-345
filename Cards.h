#ifndef TEST1_CARDS_H
#define TEST1_CARDS_H

class Card
{
public:
    void play();

private:
    Card_Type type;

};

class Deck{
public:
    void draw();

};

enum Card_Type
{
   bomb,
   reinforcement,
   blockage,
   airlift,
   diplomacy
};
#endif //TEST1_CARDS_H
