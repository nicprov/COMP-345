#include <iostream>
#include <random>
#include "Cards.h"
using namespace std;

// Card methods
Card::Card(Card_Type &type)
{
    Card::type = &type;
}

Card::Card(const Card &card)
{
    Card::type = card.type;
}

Card& Card::operator=(const Card &card)
{
    Card::type = card.type;
}

void Card::play()
{
    // TODO Create order

    // Show action
    switch (*type) {
        case bomb:
            cout << "Playing bomb card";
            break;
        case reinforcement:
            cout << "Playing reinforcement card";
            break;
        case blockade:
            cout << "Playing blockade card";
            break;
        case airlift:
            cout << "Playing airlift card";
            break;
        case diplomacy:
            cout << "Playing diplomacy card";
            break;
    }
}

std::ostream& operator<< (std::ostream &stream, const Card &card)
{
    return stream << "Card(" << card.type << ")";
}

Card::Card_Type& Card::getType()
{
    return *type;
}

// Hand methods

/**
 * Hand Constructor
 * Hand is empty initially, so not need to initialize anything with constructor
 */
Hand::Hand() {}

Hand::Hand(const Hand &hand)
{
    cards = hand.cards;
}

Hand& Hand::operator=(const Hand &hand)
{
    cards = hand.cards;
}

void Hand::addCard(Card &card)
{
    cards->push_back(card);
}

void Hand::removeCard(Card &card)
{
    for (int i=cards->size(); i > 0; i--){
        if (cards->at(i).getType() == card.getType()){
            cards->erase(cards->cbegin()+i);
            break;
        }
    }
}

std::ostream& operator<< (std::ostream &stream, const Hand &hand)
{
    stream << "Hand[";
    for (Card card: *hand.cards){
        stream << card.getType();
    }
    stream << "]";
    return stream;
}

// Deck methods
Deck::Deck()
{
    // Generates 50 cards (10 cards of each type)
    for (Card::Card_Type cardType: Card::ALL_Card_Type)
    {
        for (int i=0; i < 10; i++)
        {
            Card* card = new Card(cardType);
            cards->push_back(*card);
        }
    }
    randomEngine = std::default_random_engine {};
}

Deck::Deck(const Deck &deck)
{
    cards = deck.cards;
}

Deck& Deck::operator=(const Deck &deck)
{
    cards = deck.cards;
}

Card& Deck::draw()
{
    std::shuffle(cards->begin(), cards->end(), randomEngine);
    Card card = cards->front();
    cards->erase(cards->begin());
    return card;
}

std::ostream& operator<< (std::ostream &stream, const Deck &deck)
{
    stream << "Deck[";
    for (Card card: *deck.cards){
        stream << card.getType();
    }
    stream << "]";
    return stream;
}