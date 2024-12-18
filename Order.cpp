// 2217843_FYP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// What does the orderbook need to do.
// Buy
// Sell
// Cancel

/*

    Price, OrderID, Quantity, OrderSide, OrderType 


*/

enum class OrderType {

    LIMIT,
    CANCEL
};

enum class OrderSide {

    BUY,
    SELL

};


// fixed sizes cross platform,
// Quantity and orderID can and should never be negative
using Price = std::int32_t;
using Quantity = std::uint64_t;
using OrderId = std::uint64_t;

class Order {

public:

    // constructor
    Order(OrderId id, Quantity qty, Price price, OrderType type, OrderSide side) {
        _orderId = id;
        _quantity = qty;
        _price = price;
        _orderSide = side;
        _orderType = type;
    }

private:
    Quantity _quantity;
    OrderId _orderId;
    Price _price;
    OrderSide _orderSide;
    OrderType _orderType;


};


// good start :))
int main()
{
    std::cout << "Hello World!\n";
}
