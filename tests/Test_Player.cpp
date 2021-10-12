#include <catch2/catch_test_macros.hpp>
#include "../src/Player.h"

/**
 * Player Test cases
 */
TEST_CASE("Player constructor initializes")
{
    std::string* name = new std::string("Jonathan");
    Player player = Player(*name);
    REQUIRE(player.getName() == *name);
}

TEST_CASE("Player copy constructor initializes")
{
    std::string* name = new std::string("Jonathan");
    Player* player = new Player(*name);
    Player* player2 = new Player(*player);
    REQUIRE(*player == *player2);
}

TEST_CASE("Player assignment operator initializes")
{
    std::string* name = new std::string("Jonathan");
    Player* player = new Player(*name);
    Player* player2 = new Player(*player);
    REQUIRE(*player == *player2);
}