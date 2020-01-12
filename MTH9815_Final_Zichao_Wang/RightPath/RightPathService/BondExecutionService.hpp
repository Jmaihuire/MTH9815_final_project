//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDEXECUTIONSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDEXECUTIONSERVICE_HPP

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathGeneral/executionservice.hpp"


#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>

class BondExecutionService : public ExecutionService<Bond>
{
private:
    std::vector<ServiceListener<ExecutionOrder<Bond> >*> listenerPtrs;
    // K : cusip; V : execution order of this bond.
    std::map<std::string, ExecutionOrder<Bond> > executionData;

public:
    // ctor
    BondExecutionService() = default;

    ExecutionOrder<Bond>& GetData(std::string cusip)
    {
        return executionData.at(cusip);
    }

    void OnMessage(ExecutionOrder<Bond>& executionOrder) {}  // No implementation.

    void AddListener(ServiceListener<ExecutionOrder<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    const std::vector<ServiceListener<ExecutionOrder<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    // Execute (i.e. Print) this execution order.

    void ExecuteOrder(const ExecutionOrder<Bond>& executionOrder, Market market)
    {
        //bondExecutionServiceConnectorPtr->Publish(executionOrder);
    }


    // Use algo execution order to generate execution order,
    // and then add it into internal hash table.
    void AddAlgoExecution(const AlgoExecution& algoExeuction)
    {
        ExecutionOrder<Bond> executionOrder = algoExeuction.GetExecutionOrder();
        std::string cusip = executionOrder.GetProduct().GetProductId();
        executionData[cusip] = executionOrder;

        //std::cout << "bond execution service has: ";
        //executionData[cusip].Print();
        //std::cout << std::endl;

        // Notify all listeners.
        for(auto& listenerPtr : listenerPtrs)
            listenerPtr->ProcessAdd(executionOrder);
    }
};

#endif //MTH9815_FINAL_ZICHAO_WANG_BONDEXECUTIONSERVICE_HPP
