#include <catch2/catch_test_macros.hpp>
#include "../src/core/Player.h"
#include "../src/core/PlayerStrategies.h"

/**
 * Player Test cases
 */
TEST_CASE("Player constructor initializes")
{
    auto player = Player("Jonathan", PlayerStrategy::human);
    REQUIRE(player.getName() == "Jonathan");
    REQUIRE(player.getStrategyType() == PlayerStrategy::human);
}

TEST_CASE("Player copy constructor initializes")
{
    auto* player = new Player("Jonathan", PlayerStrategy::human);
    auto* player2 = new Player(*player);
    REQUIRE(*player == *player2);
}

TEST_CASE("Player assignment operator initializes")
{
    auto* player = new Player("Jonathan", PlayerStrategy::human);
    auto* player2 = new Player(*player);
    REQUIRE(*player == *player2);
}