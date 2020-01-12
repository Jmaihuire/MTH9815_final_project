/**
 * marketdataservice.hpp
 * Defines the data types and Service for order book market data.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 20, 2018


#ifndef MARKET_DATA_SERVICE_HPP
#define MARKET_DATA_SERVICE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Foundation/soa.hpp"

using namespace std;

// Side for market data
enum PricingSide { BID, OFFER };

/**
 * A market data order with price, quantity, and side.
 */
class Order
{
private:
    double price;
    long quantity;
    PricingSide side;

public:
    // ctor for an order
    Order() = default;

    Order(double _price, long _quantity, PricingSide _side) : price(_price), quantity(_quantity), side(_side) {}

    // Get the price on the order
    double GetPrice() const
    {
        return price;
    }

    // Get the quantity on the order
    long GetQuantity() const
    {
        return quantity;
    }

    // Get the side on the order
    PricingSide GetSide() const
    {
        return side;
    }

    // Overload assignment operator.
    Order& operator =(const Order& _order)
    {
        price = _order.GetPrice();
        quantity = _order.GetQuantity();
        side = _order.GetSide();
        return *this;
    }

    // Add two order by their quantities.
    Order& operator +=(const Order& otherOrder)
    {
        quantity += otherOrder.GetQuantity();
        return *this;
    }

    // Print order info.
    void Print()
    {
        std::cout << "price: " << price << ", quantity: " << quantity << ", side: " << ((side == BID) ? "bid" : "offer");
    }

};

// After defining operator <, we can use multiset
// instead of vector to represent order book.
bool operator < (const Order& lhsOrder, const Order& rhsOrder)
{
    if (lhsOrder.GetSide() == BID)
        return (lhsOrder.GetPrice() > rhsOrder.GetPrice());
    else
        return (lhsOrder.GetPrice() < rhsOrder.GetPrice());
}


/**
 * Class representing a bid and offer order
 */
class BidOffer
{
private:
    Order bidOrder;
    Order offerOrder;

public:
    // ctor for bid/offer
    BidOffer(const Order &_bidOrder, const Order &_offerOrder) : bidOrder(_bidOrder), offerOrder(_offerOrder) {}

    // Get the bid order
    const Order& GetBidOrder() const
    {
        return bidOrder;
    }

    // Get the offer order
    const Order& GetOfferOrder() const
    {
        return offerOrder;
    }

    // Overload assignment operator.
    BidOffer& operator =(const BidOffer& _bidOffer)
    {
        bidOrder = _bidOffer.GetBidOrder();
        offerOrder = _bidOffer.GetOfferOrder();
        return *this;
    }

    void Print()
    {
        std::cout << "Bid order: ";
        bidOrder.Print();
        std::cout << "; Offer order: ";
        offerOrder.Print();
    }

};

/**
 * Order book with a bid and offer stack.
 * Type T is the product type.
 */
template<typename T>
class OrderBook
{
private:
    T product;
    multiset<Order> bidStack;
    multiset<Order> offerStack;

public:
    // ctor for the order book
    OrderBook() = default;

    OrderBook(const T &_product, const multiset<Order> &_bidStack, const multiset<Order> &_offerStack) : product(_product), bidStack(_bidStack), offerStack(_offerStack) {}

    // Get the product
    const T& GetProduct() const
    {
        return product;
    }

    // Get the bid stack
    const multiset<Order>& GetBidStack() const
    {
        return bidStack;
    }

    // Get the offer stack
    const multiset<Order>& GetOfferStack() const
    {
        return offerStack;
    }

    OrderBook& operator =(const OrderBook& _orderBook)
    {
        product = _orderBook.GetProduct();
        bidStack = _orderBook.GetBidStack();
        offerStack = _orderBook.GetOfferStack();
        return *this;
    }

    void Print()
    {
        std::cout << "Order book CUSIP: " << product.GetProductId();
        std::cout << ", bid stack: ";
        for(auto & bidOrder : bidStack)
            std::cout << bidOrder.GetPrice() << ", ";
        std::cout << "offer stack: ";
        for(auto & offerOrder : offerStack)
            std::cout << offerOrder.GetPrice() << ", ";
    }

};

/**
 * Market Data Service which distributes market data
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class MarketDataService : public Service<string,OrderBook <T> >
{

public:
    // Get the best bid/offer order
    virtual BidOffer GetBestBidOffer(const string &productId) = 0;

    // Aggregate the order book
    virtual OrderBook<T> AggregateDepth(const string &productId) = 0;

};


#endif
