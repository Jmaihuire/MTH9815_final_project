//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDALGOEXECUTIONSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDALGOEXECUTIONSERVICE_HPP


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathGeneral/executionservice.hpp"
#include "RightPath/RightPathGeneral/marketdataservice.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>


class BondAlgoExecutionService : public Service<std::string, AlgoExecution>
{
private:
    std::vector<ServiceListener<AlgoExecution>* > listenerPtrs;
    std::map<std::string, AlgoExecution> algoExecutionData;

public:
    // ctor
    BondAlgoExecutionService() = default;

    AlgoExecution& GetData(std::string cusip)
    {
        return algoExecutionData.at(cusip);
    }

    void OnMessage(AlgoExecution& algoExecution) {}  // No implementation.

    void AddListener(ServiceListener<AlgoExecution>* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    const std::vector<ServiceListener<AlgoExecution>* > & GetListeners() const
    {
        return listenerPtrs;
    }

    // Use a new order book to generate a new algo execution,
    // and then add this algo execution into internal hash table.
    void AddOrderBook(OrderBook<Bond>& orderBook)
    {
        Bond bond = orderBook.GetProduct();
        std::string cusip = bond.GetProductId();

        AlgoExecution * algoExecutionPtr;
        auto iter = algoExecutionData.find(cusip);

        if(iter != algoExecutionData.end())
        {
            algoExecutionPtr = &(iter->second);
            algoExecutionPtr->UpdateOrderBook(orderBook);
        }
        else
        {
            //AlgoExecution newAlgoExecution(orderBook);
            //std::cout << "A" << std::endl;
            algoExecutionData.insert(std::pair<std::string, AlgoExecution>(cusip, AlgoExecution(orderBook)));
            //std::cout << "B" << std::Endl;
            algoExecutionPtr = &(algoExecutionData[cusip]);
        }

        //std::cout << "bond algo execution service has: ";
        //(algoExecutionPtr->GetExecutionOrder()).Print();
        //std::cout << std::endl;

        // Notify all listeners.
        for(auto& listenerPtr : listenerPtrs)
            listenerPtr->ProcessAdd(*algoExecutionPtr);

    }

};



#endif //MTH9815_FINAL_ZICHAO_WANG_BONDALGOEXECUTIONSERVICE_HPP
