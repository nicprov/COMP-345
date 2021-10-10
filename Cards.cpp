#include <iostream>
#include <random>
#include "Cards.h"

// Card methods
Card::Card(CardType type)
{
    this->type = new CardType(type);
}

Card::Card(const Card *card) {
    this->type = new CardType(*card->type);
}

Card& Card::operator=(const Card &card)
{
    this->type = new CardType(*card.type);
    return *this;
}

void Card::play()
{
    // TODO Create order

    // Show action
    switch (*type) {
        case bomb:
            std::cout << "Playing bomb card";
            break;
        case reinforcement:
            std::cout << "Playing reinforcement card";
            break;
        case blockade:
            std::cout << "Playing blockade card";
            break;
        case airlift:
            std::cout << "Playing airlift card";
            break;
        case diplomacy:
            std::cout << "Playing diplomacy card";
            break;
    }
}

std::ostream& operator<< (std::ostream &stream, const Card &card)
{
    return stream << "Card(" << *card.type << ")";
}

std::ostream& operator<< (std::ostream &stream, const Card::CardType &cardType)
{
    switch (cardType) {
        case Card::CardType::bomb:
            stream << "Bomb";
            break;
        case Card::CardType::diplomacy:
            stream << "Diplomacy";
            break;
        case Card::CardType::airlift:
            stream << "Airlift";
            break;
        case Card::CardType::blockade:
            stream << "Blockade";
            break;
        case Card::CardType::reinforcement:
            stream << "Reinforcement";
            break;
    }
    return stream;
}

Card::CardType& Card::getType()
{
    return *type;
}

bool Card::operator==(const Card &card) const
{
    return this->type == card.type;
}

// Hand methods

/**
 * Hand Constructor
 * Hand is empty initially, so not need to initialize anything with constructor
 */
Hand::Hand() {
    this->cards = new std::vector<Card>;
}

Hand::Hand(const Hand *hand)
{
    this->cards = new std::vector(*hand->cards);
}

Hand& Hand::operator=(const Hand &hand)
{
    this->cards = new std::vector(*hand.cards);
    return *this;
}

void Hand::addCard(Card &card)
{
    this->cards->push_back(card);
}

void Hand::removeCard(Card &card)
{
    for (int i=this->cards->size()-1; i >= 0; i--){
        if (this->cards->at(i).getType() == card.getType()){
            this->cards->erase(this->cards->cbegin()+i);
            break;
        }
    }
}

std::ostream& operator<< (std::ostream &stream, const Hand &hand)
{
    stream << "Hand[";
    int counter = 1;
    for (Card card: *hand.cards){
        if (counter++ < hand.cards->size())
            stream << card.getType() << ",";
        else
            stream << card.getType();
    }
    stream << "]";
    return stream;
}

std::vector<Card> Hand::getCards()
{
    return *this->cards;
}

bool Hand::operator==(const Hand &hand) const
{
    return this->cards == hand.cards;
}

// Deck methods
Deck::Deck()
{
    this->cards = new std::vector<Card>;
    // Generates 50 cards (10 cards of each type)
    for (Card::CardType cardType: Card::ALL_Card_Type)
    {
        for (int i=0; i < Deck::NUM_CARDS_PER_TYPE; i++)
        {
            this->cards->push_back(Card(cardType));
        }
    }
}

Deck::Deck(const Deck *deck)
{
    this->cards = new std::vector(*deck->cards);
}

Deck& Deck::operator=(const Deck &deck)
{
    this->cards = new std::vector(*deck.cards);
    return *this;
}

Card& Deck::draw()
{
    if (this->cards->size() > 0){
        shuffle(cards->begin(), cards->end(), std::random_device {});
        Card* card = new Card(cards->front());
        cards->erase(cards->begin());
        return *card;
    } else
        throw std::runtime_error("No more cards to draw");
}

std::ostream& operator<< (std::ostream &stream, const Deck &deck)
{
    stream << "Deck[";
    int counter = 1;
    for (Card card: *deck.cards){
        if (counter++ < deck.cards->size())
            stream << card.getType() << ",";
        else
            stream << card.getType();
    }
    stream << "]";
    return stream;
}

std::vector<Card> Deck::getCards()
{
    return *this->cards;
}

bool Deck::operator==(const Deck &deck) const
{
    return this->cards == deck.cards;
}
