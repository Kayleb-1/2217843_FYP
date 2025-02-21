#include <iostream>
#include <string>
#include <map>
#include <unordered_map>


enum class OrderType {

    MARKET,
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
        _initialQuantity = qty;
        _price = price;
        _orderSide = side;
        _orderType = type;
    }

    int a { 5 };

    // Fill logic for order, cannot reduce past current ammout
    void Fill(Quantity qty) {
        if (qty > _quantity) {
            return;
        }

        _quantity -= qty;
    }

    OrderSide getSide()     { return _orderSide; }
    OrderType getType()     { return _orderType; }
    Price getPrice()        { return _price; }
    Quantity getQuantity()  { return _quantity; }
    



private:
    // Price, OrderID, Quantity, OrderSide, OrderType

    Quantity _quantity;
    Quantity _initialQuantity;
    OrderId _orderId;
    Price _price;
    OrderSide _orderSide;
    OrderType _orderType;


};


using OrderPointer = std::shared_ptr<Order>;


/*
    Should atleast support

    Add order (Buy/Sell)
    Cancel (important to account for in simulations due to 80% order cancel rate

*/

class Orderbook {
private:

    // Orders grouped by price --  15$ :  [ OrderId, Quantity etc...]
    std::map<Price, std::vector<Order>, std::greater<Price>> bids;
    std::map<Price, std::vector<Order>> asks;

    std::unordered_map<OrderId, Order> orderMap;

public:

    bool CanMatch() {



    }

    // Get best of both books, match if possible
    void MatchOrders() {

        if (!CanMatch()) { return; }


        while (true) {

            if (bids.empty() || asks.empty()) break;

            auto bidIt = bids.begin();
            auto askIt = asks.begin();

            Price bidPrice = bidIt->first;
            Price askPrice = askIt->first;

            while (bids.size() && asks.size()) {

                if (askPrice < bidPrice) {
                     
                    // pointer >> if order is large? (or is naive)
                    auto bidLevel = bidIt->second;
                    auto askLevel = askIt->second;

                    Order bidOrder = bidLevel.front();
                    Order askOrder = askLevel.front();

                    Quantity bidQuantity{ bidOrder.getQuantity() };
                    Quantity askQuantity{ askOrder.getQuantity() };

                    if (askQuantity > bidQuantity) {
                        askOrder.Fill(bidQuantity);
                        bidOrder.Fill(bidQuantity);

                        //bids.
                    }
                    else {
                        askOrder.Fill(askQuantity);
                        bidOrder.Fill(askQuantity);
                    }

                }
            }

            

            
        }
    }


    // needs to return some data on what was traded (if anything was traded
    void AddOrder(Quantity qty, Price price, OrderType type, OrderSide side) {

        // scheme for new orderids (prob j increment)
        // static placeholder
        OrderId r{ 11234 };



        if (type == OrderType::MARKET) {
            price = 0;
        }

        Order newOrder{ r, qty, price, type, side };


        // prob bad practice (read up on pointer logic :)) )
        // Order* orderpointer{ &newOrder };
        orderMap[r] = newOrder;

        if (side == OrderSide::BUY) {
            bids[price].push_back(newOrder);

        }
        else
        {
            asks[price].push_back(newOrder);
        }

        orderMap.insert({ r, newOrder });
        MatchOrders();

    }
};



// good start :))
int main()
{
    Order myorder { 51, 511, 51, OrderType::LIMIT, OrderSide::BUY };
}
