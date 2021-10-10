#include <catch2/catch_test_macros.hpp>
#include "../Cards.h"

TEST_CASE("Card initializes properly"){
    REQUIRE_NOTHROW(Card(Card::reinforcement));
}

TEST_CASE("Card get type"){
    Card card = Card::blockade;
    REQUIRE(card.getType() == Card::blockade);
}

TEST_CASE("Hand initializes properly"){
    REQUIRE_NOTHROW(Hand());
}

TEST_CASE("Deck initializes properly"){
    REQUIRE_NOTHROW(Deck());
}
TEST_CASE("Deck throws exception when out of cards"){
    Deck deck = Deck();
    for (int i=0; i<(Deck::NUM_CARDS_PER_TYPE*5)+1; i++){
        if (i == (Deck::NUM_CARDS_PER_TYPE*5))
            REQUIRE_THROWS_AS(deck.draw(), std::runtime_error);
        else
            deck.draw();
    }
}


