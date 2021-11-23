#include <catch2/catch_test_macros.hpp>
#include "../src/core/Orders.h"
#include "../src/core/Player.h"
#include "../src/core/Map.h"
#include "../src/core/PlayerStrategies.h"

/**
 * Order Test cases
 */
TEST_CASE("Order constructor initializes and get type")
{
    Order* order = new Bomb(Order::OrderType::bomb, new Player("john", PlayerStrategy::human), new Territory());
    REQUIRE(order->getOrderType() == Order::OrderType::bomb);
}

TEST_CASE("Order copy constructor initializes")
{
    Order* order = new Deploy(Order::OrderType::deploy, new Player("test", PlayerStrategy::human), new Territory(), 0);
    Order* order2 = new Deploy(*dynamic_cast<Deploy*>(order));
    REQUIRE(*order == *order2);
}

TEST_CASE("Order assignment operator initializes")
{
    Order* order = new Deploy(Order::OrderType::deploy, new Player("test", PlayerStrategy::human), new Territory(), 0);
    Order* order2 = order;
    REQUIRE(*order == *order2);
}

/**
 * OrderList Test cases
 */

TEST_CASE("OrderList constructor initializes")
{
    auto* orderList = new OrderList();
    REQUIRE(orderList->getOrders() == std::vector<Order*>{});
}

TEST_CASE("OrderList copy constructor initializes")
{
    auto* orderList = new OrderList();
    orderList->add(new Deploy(Order::OrderType::deploy, new Player("test", PlayerStrategy::human), new Territory(), 0));
    auto* orderList2 = new OrderList(*orderList);
    REQUIRE(*orderList == *orderList2);
}

TEST_CASE("OrderList assignment operator initializes")
{
    OrderList* orderList = new OrderList();
    orderList->add(new Deploy(Order::OrderType::deploy, new Player("test", PlayerStrategy::human), new Territory(), 0));
    OrderList* orderList2 = orderList;
    REQUIRE(*orderList == *orderList2);
}

TEST_CASE("OrderList remove order out of range")
{
    OrderList orderList;
    REQUIRE_THROWS_AS(orderList.remove(1), std::runtime_error);
}