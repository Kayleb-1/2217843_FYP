#include <iostream>
#include <map>
#include <unordered_map>


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
using Price = std::double_t;
using Quantity = std::uint64_t;
using OrderId = std::uint64_t;



/*
    Order - Class functions for a particular order, required functions tbd,
    TODO: proper implementation of updates of quantity(fills)
*/
class Order {

public:

    // constructor
    Order(OrderId id, Quantity qty, Price price, OrderType type, OrderSide side) {
        _orderId = id;
        _quantity = qty;
        _currentQuantity = qty;

        _price = price;
        _orderSide = side;
        _orderType = type;
    }

    // Fill logic for order, cannot reduce past current ammout
    void Fill(Quantity qty) {
        if (qty > _currentQuantity) {
            return;
        }

        _currentQuantity -= qty;
    }

private:
    // Price, OrderID, Quantity, OrderSide, OrderType

    Quantity _quantity;
    Quantity _currentQuantity;
    OrderId _orderId;
    Price _price;
    OrderSide _orderSide;
    OrderType _orderType;


};


/*
    Should atleast support

    Add order (Buy/Sell)
    Cancel (important to account for in simulations due to 80% order cancel rate

*/

class Orderbook {

    // Orders grouped by price --  15$ : 
    std::map<


};



// good start :))
int main()
{
    Order myorder = Order(51, 511, 51, OrderType::LIMIT, OrderSide::BUY);
}
