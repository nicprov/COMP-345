#include <catch2/catch_test_macros.hpp>
#include "../src/core/Map.h"

/**
 * Map Test cases
 */
TEST_CASE("Map constructor initializes")
{
    Map* map = new Map("test");
    REQUIRE(map->getMapName() == "test");
}

TEST_CASE("Map copy constructor initializes")
{
    Map* map = new Map("test");
    Map* map2 = new Map(*map);
    REQUIRE(*map == *map2);
}

TEST_CASE("Map assignment operator initializes")
{
    Map* map = new Map("test");
    Map* map2 = map;
    REQUIRE(*map == *map2);
}

/**
 * Territory Test cases
 */
TEST_CASE("Territory constructor initializes")
{
    Territory* territory = new Territory(1, "test", 1);
    REQUIRE(territory->getTerrIndex() == 1);
    REQUIRE(territory->getTerrName() == "test");
    REQUIRE(territory->getContIndex() == 1);
}

TEST_CASE("Territory copy constructor initializes")
{
    Territory* territory = new Territory(1, "test", 1);
    Territory* territory2 = new Territory(*territory);
    REQUIRE(*territory == *territory2);

}

TEST_CASE("Territory assignment operator initializes")
{
    Territory* territory = new Territory(1, "test", 1);
    Territory* territory2 = territory;
    REQUIRE(*territory == *territory2);
}

/**
 * Continent Test cases
 */
TEST_CASE("Continent constructor initializes")
{
    Continent* continent = new Continent(1, "test", 1);
    REQUIRE(continent->getCIndex() == 1);
    REQUIRE(continent->getContName() == "test");
    REQUIRE(continent->getArmyValue() == 1);
}

TEST_CASE("Continent copy constructor initializes")
{
    Continent* continent = new Continent(1, "test", 1);
    Continent* continent2 = new Continent(*continent);
    REQUIRE(*continent == *continent2);
}

TEST_CASE("Continent assignment operator initializes")
{
    Continent* continent = new Continent(1, "test", 1);
    Continent* continent2 = continent;
    REQUIRE(*continent == *continent2);
}