#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "../src/core/Cards.h"

/**
 * CARD Test cases
 */
TEST_CASE("Card constructor initializes")
{
    Card card = Card(Card::CardType::blockade);
    REQUIRE(card.getType() == Card::CardType::blockade);
}

TEST_CASE("Card copy constructor initializes")
{
    Card* card = new Card(Card::CardType::reinforcement);
    Card* card2 = new Card(*card);
    REQUIRE(*card == *card2);
}

TEST_CASE("Card assignment operator initializes")
{
    Card* card = new Card(Card::CardType::reinforcement);
    Card* card2 = card;
    REQUIRE(card == card2);
}

TEST_CASE("Card get type function returns proper type")
{
    Card card = Card::blockade;
    REQUIRE(card.getType() == Card::blockade);
}


/**
 * Hand Test cases
 */
TEST_CASE("Hand constructor initializes")
{
    Hand* hand = new Hand();
    REQUIRE(hand->getCards() == std::vector<Card*> {});
}

TEST_CASE("Hand copy constructor initializes")
{
    Hand* hand = new Hand();
    Hand* hand2 = new Hand(*hand);
    REQUIRE(*hand == *hand2);
}

TEST_CASE("Hand assignment operator initializes")
{
    Hand* hand = new Hand();
    Hand* hand2 = hand;
    REQUIRE(*hand == *hand2);
}

TEST_CASE("Hand can add card")
{
    Hand hand;
    Card* card = new Card(Card::CardType::blockade);
    hand.addCard(card);
    std::vector<Card*> cards = hand.getCards();
    REQUIRE(std::find(cards.begin(), cards.end(), card) != cards.end());
}

TEST_CASE("Hand can remove card")
{
    Hand hand;
    Card* card = new Card(Card::CardType::reinforcement);
    hand.addCard(card);
    hand.removeCard(card);
    std::vector<Card*> cards = hand.getCards();
    REQUIRE(!(std::find(cards.begin(), cards.end(), card) != cards.end()));
}

TEST_CASE("Hand can get cards")
{
    Hand* hand = new Hand();
    Card* card = new Card(Card::CardType::blockade);
    hand->addCard(card);
    hand->addCard(card);
    std::vector<Card*> cards = hand->getCards();
    REQUIRE(cards.size() == 2);
}


/**
 * Deck Test cases
 */
TEST_CASE("Deck constructor initializes")
{
    Deck deck = Deck();
    std::vector<Card> cards;
    int incrementor = 0;
    for (Card::CardType cardType: Card::ALL_Card_Type)
    {
        for (int i=0+incrementor; i < Deck::NUM_CARDS_PER_TYPE+incrementor; i++)
        {
            REQUIRE(deck.getCards().at(i)->getType() == cardType);
        }
        incrementor += Deck::NUM_CARDS_PER_TYPE;
    }
}

TEST_CASE("Deck copy constructor initializes")
{
    Deck* deck = new Deck();
    Deck* deck2 = new Deck(*deck);
    REQUIRE(*deck == *deck2);
}

TEST_CASE("Deck assignment operator initializes")
{
    Deck* deck = new Deck();
    Deck* deck2 = new Deck(*deck);
    REQUIRE(*deck == *deck2);
}

TEST_CASE("Deck draw removes card from deck")
{
    Deck* deck = new Deck();
    deck->draw();
    REQUIRE(deck->getCards().size() == 49);
}

TEST_CASE("Deck get cards")
{
    Deck* deck = new Deck();
    REQUIRE(deck->getCards().size() == 50);
}

TEST_CASE("Deck throws exception when out of cards")
{
    Deck deck = Deck();
    for (int i=0; i<(Deck::NUM_CARDS_PER_TYPE*5)+1; i++){
        if (i == (Deck::NUM_CARDS_PER_TYPE*5))
            REQUIRE_THROWS_AS(deck.draw(), std::runtime_error);
        else
            deck.draw();
    }
}


