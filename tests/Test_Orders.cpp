#include <catch2/catch_test_macros.hpp>
#include "../src/Orders.h"

/**
 * Order Test cases
 */
TEST_CASE("Order constructor initializes and get type")
{
    Order order = Order(Order::OrderType::advance);
    REQUIRE(order.getOrderType() == Order::OrderType::advance);
}

TEST_CASE("Order copy constructor initializes")
{
    Order order = Order(Order::OrderType::deploy);
    Order order2 = Order(order);
    REQUIRE(order == order2);
}

TEST_CASE("Order assignment operator initializes")
{
    Order order = Order(Order::OrderType::deploy);
    Order order2 = order;
    REQUIRE(order == order2);
}

/**
 * OrderList Test cases
 */

TEST_CASE("OrderList constructor initializes")
{
    OrderList orderList;
    REQUIRE(orderList.getOrders() == std::vector<Order>{});
}

TEST_CASE("OrderList copy constructor initializes")
{
    OrderList orderList;
    orderList.add(new Order(Order::OrderType::advance));
    OrderList orderList2 = OrderList(orderList);
    REQUIRE(orderList == orderList2);
}

TEST_CASE("OrderList assignment operator initializes")
{
    OrderList orderList;
    orderList.add(new Order(Order::OrderType::advance));
    OrderList orderList2 = orderList;
    REQUIRE(orderList == orderList2);
}