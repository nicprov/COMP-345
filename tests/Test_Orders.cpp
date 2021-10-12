#include <catch2/catch_test_macros.hpp>
#include "../src/Orders.h"

/**
 * Order Test cases
 */
TEST_CASE("Order constructor initializes and get type")
{
    Order* order = new Order(Order::OrderType::advance);
    REQUIRE(order->getOrderType() == Order::OrderType::advance);
}

TEST_CASE("Order copy constructor initializes")
{
    Order* order = new Order(Order::OrderType::deploy);
    Order* order2 = new Order(*order);
    REQUIRE(*order == *order2);
}

TEST_CASE("Order assignment operator initializes")
{
    Order* order = new Order(Order::OrderType::deploy);
    Order* order2 = order;
    REQUIRE(*order == *order2);
}

/**
 * OrderList Test cases
 */

TEST_CASE("OrderList constructor initializes")
{
    OrderList* orderList = new OrderList();
    REQUIRE(orderList->getOrders() == std::vector<Order*>{});
}

TEST_CASE("OrderList copy constructor initializes")
{
    OrderList* orderList = new OrderList();
    orderList->add(new Order(Order::OrderType::advance));
    OrderList* orderList2 = new OrderList(*orderList);
    REQUIRE(*orderList == *orderList2);
}

TEST_CASE("OrderList assignment operator initializes")
{
    OrderList* orderList = new OrderList();
    orderList->add(new Order(Order::OrderType::advance));
    OrderList* orderList2 = orderList;
    REQUIRE(*orderList == *orderList2);
}

TEST_CASE("OrderList remove order out of range")
{
    OrderList orderList;
    REQUIRE_THROWS_AS(orderList.remove(1), std::runtime_error);
}