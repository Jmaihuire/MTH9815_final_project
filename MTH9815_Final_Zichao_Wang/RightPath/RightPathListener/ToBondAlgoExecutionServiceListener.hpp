//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDALGOEXECUTIONSERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDALGOEXECUTIONSERVICELISTENER_HPP

// data flow:
// BondMarketDataService --> ToBondAlgoExecutionServiceListener --> BondAlgoExecutionService


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathGeneral/marketdataservice.hpp"
#include "RightPath/RightPathService/BondAlgoExecutionService.hpp"


class ToBondAlgoExecutionServiceListener : public ServiceListener<OrderBook<Bond> >
{
private:
    BondAlgoExecutionService* bondAlgoExecutionServicePtr;

public:
    // ctor
    ToBondAlgoExecutionServiceListener(BondAlgoExecutionService* _bondAlgoExecutionServicePtr) : bondAlgoExecutionServicePtr(_bondAlgoExecutionServicePtr) {}

    void ProcessAdd(OrderBook<Bond>& orderBook)
    {
        //std::cout << "to bond algo execution service receives: ";
        //orderBook.Print();
        //std::cout << std::endl;

        bondAlgoExecutionServicePtr->AddOrderBook(orderBook);
    }

    void ProcessRemove(OrderBook<Bond>& orderBook) {}  // No implementation.

    void ProcessUpdate(OrderBook<Bond>& orderBook) {}  // No implementation.
};


#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDALGOEXECUTIONSERVICELISTENER_HPP
