//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDMARKETDATASERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDMARKETDATASERVICE_HPP

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathGeneral/marketdataservice.hpp"

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <set>


class BondMarketDataService : public MarketDataService<Bond>
{
private:
    std::vector<ServiceListener<OrderBook<Bond> >*> listenerPtrs;
    // K : CUSIP; V : order book of this bond.
    std::map<std::string, OrderBook<Bond> > marketData;

    // Combine an order book to eliminate order with same sides and prices.
    std::multiset<Order> Combine(const std::multiset<Order>& oldOrderBook);

public:
    // ctor
    BondMarketDataService() = default;

    OrderBook<Bond>& GetData(std::string cusip)
    {
        return marketData.at(cusip);
    }

    // Update hash table using new order book and notify listners.
    void OnMessage(OrderBook<Bond>& orderBook)
    {
        // Update order book of this particular bond,
        // and get aggregated order book.
        marketData[orderBook.GetProduct().GetProductId()] = orderBook;
        OrderBook<Bond> aggregatedOrderBook = AggregateDepth(orderBook.GetProduct().GetProductId());

        //std::cout << "bond market data service receives: ";
        //orderBook.Print();
        //std::cout << std::endl;

        // Pass this aggregated order book to all listeners.
        for(auto & listenerPtr : listenerPtrs)
            listenerPtr->ProcessAdd(aggregatedOrderBook);
    }

    void AddListener(ServiceListener<OrderBook<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    const std::vector<ServiceListener<OrderBook<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    BidOffer GetBestBidOffer(const std::string & cusip)
    {
        OrderBook<Bond>& orderBook = marketData.at(cusip);
        return BidOffer(*orderBook.GetBidStack().begin(), *orderBook.GetOfferStack().begin());
    }

    // Aggregate both sides of the order book of given bond,
    // and return the aggregated order book.
    OrderBook<Bond> AggregateDepth(const std::string & cusip)
    {
        OrderBook<Bond>& orderBook = marketData.at(cusip);
        return OrderBook<Bond>(orderBook.GetProduct(), Combine(orderBook.GetBidStack()), Combine(orderBook.GetOfferStack()));
    }
};


std::multiset<Order> BondMarketDataService::Combine(const std::multiset<Order>& oldOrderBook)
{
    // to store the combined order book.
    std::multiset<Order> newOrderBook;

    auto nextIterator = oldOrderBook.begin();
    auto prevOrder = *(nextIterator++);

    for(; nextIterator != oldOrderBook.end(); nextIterator++)
    {
        // If two prices are different, we do not need to combine.
        if(prevOrder.GetPrice() != nextIterator->GetPrice())
        {
            newOrderBook.insert(prevOrder);
            prevOrder = *nextIterator;
        }
        // Otherwise we combine these two orders.
        else
            prevOrder += *nextIterator;
    }

    newOrderBook.insert(prevOrder);
    return newOrderBook;
}

#endif //MTH9815_FINAL_ZICHAO_WANG_BONDMARKETDATASERVICE_HPP
