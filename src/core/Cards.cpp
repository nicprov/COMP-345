#include <iostream>
#include <random>
#include "Cards.h"

// Card methods
/**
 * Card constructor
 * @param type CardType enum
 */
Card::Card(CardType type)
{
    this->type = new CardType(type);
}

/**
 * Card copy constructor
 * Makes a copy of Card
 * @param card CardType enum
 */
Card::Card(const Card &card)
{
    this->type = new CardType(*card.type);
}

/**
 * Card assignment operator
 * @param card CardType enum
 * @return Card reference
 */
Card& Card::operator=(const Card &card)
{
    this->type = new CardType(*card.type);
    return *this;
}

/**
 * Plays a card from the hand by creating an order in the order list, and returns the card to the deck
 * @param hand Hand to remove the card from
 * @param deck Deck to place the card back in
 */
void Card::play(Deck* deck, Player* player, Map* map, std::vector<Player*> players)
{
    // Add card back to deck
    deck->returnCard(this);
    player->hand->removeCard(this);

    Order* order;
    Territory* territoryTo;
    Territory* territoryToAttack;
    Territory* territoryFrom;
    Territory* territoryToBlockade;
    Player* enemy;
    int index = 0;

    switch (*this->type) {
        case bomb:
            std::cout << "Playing bomb card..." << std::endl;

            // Display territories available for bombing
            index = 1;
            std::cout << "List of available territories to bomb: " << std::endl;
            for (Territory* canAttack : player->toAttack(map)) {
                std::cout << index++ << ". " << canAttack->getTerrName() << std::endl;
            }

            // Ask for territory to bomb
            std::cout << "Select territory to bomb: ";
            int territoryToAttackIndex;
            getValidatedInput(territoryToAttackIndex, 1, player->toAttack(map).size());
            territoryToAttack = player->toAttack(map).at(territoryToAttackIndex-1);

            // Create order and add to order list
            order = new Bomb(Order::OrderType::bomb, territoryToAttack->getOwner(), territoryToAttack);
            player->orderList->add(order);
            break;
        case blockade:
            std::cout << "Playing blockade card..." << std::endl;

            // List owned territories
            index = 1;
            std::cout << "List of available territories to blockade: " << std::endl;
            for (Territory* canAttack : player->toDefend(map)) {
                std::cout << index++ << ". " << canAttack->getTerrName() << std::endl;
            }

            //Ask territory to blockade
            std::cout << "Select territory to blockade: ";
            int territoryToBlockadeIndex;
            getValidatedInput(territoryToBlockadeIndex, 1, player->toDefend(map).size());
            territoryToBlockade = player->toDefend(map).at(territoryToBlockadeIndex-1);

            order = new Blockade(Order::OrderType::blockade, player, territoryToBlockade);
            attachExistingObservers(order, player->orderList->getObservers());
            player->orderList->add(order);
            break;
        case airlift:
            std::cout << "Playing airlift card..." << std::endl;

            // List owned territories
            index = 1;
            std::cout << "List of available territories owned: " << std::endl;
            for (Territory* canAttack : player->toDefend(map)) {
                std::cout << index++ << ". " << canAttack->getTerrName() << " (armies: " << canAttack->getNumberOfArmies() << ")" << std::endl;
            }

            // Ask source territory
            std::cout << "Select a territory to mobilize armies from: " << std::endl;
            int territoryFromIndex;
            getValidatedInput(territoryFromIndex, 1, player->toDefend(map).size());
            territoryFrom = player->toDefend(map).at(territoryFromIndex-1);

            // Ask destination territory
            std::cout << "Select a territory to mobilize armies to: " << std::endl;
            int territoryToIndex;
            getValidatedInput(territoryToIndex, 1, player->toDefend(map).size());
            territoryTo = player->toDefend(map).at(territoryToIndex-1);

            // Ask for number of armies to deploy
            std::cout << "Select the number of armies to deploy: ";
            int armiesToDeploy;
            getValidatedInput(armiesToDeploy, 1, territoryFrom->getNumberOfArmies());

            order = new Airlift(Order::OrderType::advance, player, territoryFrom, territoryTo, armiesToDeploy);
            attachExistingObservers(order, player->orderList->getObservers());
            player->orderList->add(order);
            break;
        case diplomacy:
            std::cout << "Playing diplomacy card..." << std::endl;

            // Display players in the game
            index = 0;
            for (Player* _player : players) {
                std::cout << index++ << ". " << player->getName() << std::endl;
            }

            // Ask player to negotiate with
            std::cout << "Select player with whom to negotiate (cannot negotiate with oneself): ";
            int enemyIndex;
            getValidatedInput(enemyIndex, 1, players.size());
            enemy = players.at(enemyIndex-1);

            order = new Negotiate(Order::OrderType::negotiate, player, enemy);
            attachExistingObservers(order, player->orderList->getObservers());
            player->orderList->add(order);
            break;
        case reinforcement:
            std::cout << "Playing reinforcement card..." << std::endl;
            // Immediately adds 5 armies in the reinforcement pool
            player->armyPool += 5;
            break;
    }
}

/**
 * Stream insertion operator for card
 * @param stream Output stream
 * @param card Card
 * @return Output stream
 */
std::ostream& operator<< (std::ostream &stream, const Card &card)
{
    return stream << "Card(" << *card.type << ")";
}

/**
 * Stream insertion operator for card type
 * @param stream Output strema
 * @param cardType CardType
 * @return Output stream
 */
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

/**
 * Get card type pointer
 * @return CardType pointer
 */
Card::CardType& Card::getType()
{
    return *type;
}

/**
 * Compares cards by looking at their type
 * @param card Card compared to
 * @return True (if match, false otherwise)
 */
bool Card::operator==(const Card &card) const
{
    return *this->type == *card.type;
}

// Hand methods
/**
 * Hand destructor
 */
Hand::~Hand()
{
    for (Card* card: this->cards)
    {
        delete card;
    }
}

/**
 * Hand constructor
 */
Hand::Hand()
{
    this->cards = std::vector<Card*>();
}

/**
 * Hand constructor
 * @param hand Hand to copy
 */
Hand::Hand(const Hand &hand)
{
    this->cards = std::vector<Card*>();
    for (auto* card: hand.cards)
        this->cards.push_back(new Card(*card));
}

/**
 * Hand assignment operator
 * @param hand Hand to copy
 * @return New copied hand
 */
Hand& Hand::operator=(const Hand &hand)
{
    if (this != &hand){
        for (Card* card: this->cards)
            delete card;
        this->cards = std::vector<Card*>();
        for (Card* card: hand.cards)
            this->cards.push_back(new Card(*card));
    }
    return *this;
}

/**
 * Add card to hand
 * @param card Card to add
 */
void Hand::addCard(Card *card)
{
    this->cards.push_back(card);
}

/**
 * Remove card from hand
 * @param card Card to remove
 */
void Hand::removeCard(Card *card)
{
    for (int i=this->cards.size()-1; i >= 0; i--)
    {
        if (this->cards.at(i)->getType() == card->getType())
        {
            this->cards.erase(this->cards.cbegin()+i);
            break;
        }
    }
}

/**
 * Hand stream insertion operator
 * @param stream Output stream
 * @param hand Hand to print
 * @return output stream
 */
std::ostream& operator<< (std::ostream &stream, const Hand &hand)
{
    stream << "Hand[";
    int counter = 1;
    for (Card *card: hand.cards)
    {
        if (counter++ < hand.cards.size())
            stream << card->getType() << ",";
        else
            stream << card->getType();
    }
    stream << "]";
    return stream;
}

/**
 * Get all cards from hand
 * @return list of cards in hand
 */
std::vector<Card*> Hand::getCards()
{
    return this->cards;
}

/**
 * Compares hands by looking at the list of cards
 * @param hand Hand to compare
 * @return True (if the list of cards match), False otherwise
 */
bool Hand::operator==(const Hand &hand) const
{
    return hand.cards == this->cards;
}

// Deck methods
/**
 * Deck destructor
 */
Deck::~Deck()
{
    for (Card* card: this->cards)
    {
        delete card;
    }
}

/**
 * Deck constructor
 */
Deck::Deck()
{
    this->cards = std::vector<Card*>();
    // Generates 50 cards (10 cards of each type)
    for (Card::CardType cardType: Card::ALL_Card_Type)
    {
        for (int i=0; i < Deck::NUM_CARDS_PER_TYPE; i++)
        {
            Card* card = new Card(cardType);
            this->cards.push_back(card);
        }
    }
}

/**
 * Deck copy constructor
 * @param deck Deck to copy
 */
Deck::Deck(const Deck &deck)
{
    this->cards = std::vector<Card*>();
    for (Card* card: deck.cards)
        this->cards.push_back(new Card(*card));
}

/**
 * Deck assignment operator
 * @param deck Deck to copy
 * @return Copied deck
 */
Deck& Deck::operator=(const Deck &deck)
{
    if (this != &deck){
        for (Card* card: this->cards)
            delete card;
        this->cards = std::vector<Card*>();
        for (Card* card: deck.cards)
            this->cards.push_back(new Card(*card));
    }
    return *this;
}

/**
 * Shuffle deck and get a random card
 * @return Random card
 */
Card* Deck::draw()
{
    if (this->cards.size() > 0)
    {
        shuffle(cards.begin(), cards.end(), std::random_device {});
        Card* card = new Card(*cards.front());
        cards.erase(cards.begin());
        return card;
    } else
        throw std::runtime_error("No more cards to draw");
}

/**
 * Deck stream insertion operator
 * @param stream Output stream
 * @param deck Deck to print
 * @return Output stream
 */
std::ostream& operator<< (std::ostream &stream, const Deck &deck)
{
    stream << "Deck[";
    int counter = 1;
    for (Card* card: deck.cards)
    {
        if (counter++ < deck.cards.size())
            stream << card->getType() << ",";
        else
            stream << card->getType();
    }
    stream << "]";
    return stream;
}

/**
 * Gets a list of cards in deck
 * @return List of cards in deck
 */
std::vector<Card*> Deck::getCards()
{
    return this->cards;
}

/**
 * Compares deck by looking at the list of cards
 * @param deck Deck to copy
 * @return Newly copied deck
 */
bool Deck::operator==(const Deck &deck) const
{
    int counter = 0;
    for (Card* card: deck.cards)
        if (!(*this->cards.at(counter++) == *card))
            return false;
    return true;
}

/**
 * Return card back to deck
 * @param card Card to return to deck
 */
void Deck::returnCard(Card *card)
{
    this->cards.push_back(card);
}

void Deck::setCards(std::vector<Card*>& _cards)
{
    this->cards = _cards;
}

void Card::attachExistingObservers(Subject *subject, const std::vector<Observer*>& observerList) {
    for (Observer* observer: observerList)
        subject->attach(observer);
}