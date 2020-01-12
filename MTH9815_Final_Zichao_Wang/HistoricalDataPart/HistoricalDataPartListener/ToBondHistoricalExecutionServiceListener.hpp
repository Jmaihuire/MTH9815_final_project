//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALEXECUTIONSERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALEXECUTIONSERVICELISTENER_HPP


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathGeneral/executionservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalExecutionService.hpp"


class ToBondHistoricalExecutionServiceListener : public ServiceListener<ExecutionOrder<Bond> >
{
private:
    BondHistoricalExecutionService* bondHistoricalExecutionServicePtr;

public:
    // ctor
    ToBondHistoricalExecutionServiceListener(BondHistoricalExecutionService* _bondHistoricalExecutionServicePtr) : bondHistoricalExecutionServicePtr(_bondHistoricalExecutionServicePtr) {}

    void ProcessAdd(ExecutionOrder<Bond>& executionOrder)
    {
        // Notify inquiry service.
        //bondHistoricalStreamingServicePtr->OnMessage(position);

        //std::cout << "to bond historical execution service listener has: ";
        //executionOrder.Print();
        //std::cout << std::endl;

        // Publish execution order.
        bondHistoricalExecutionServicePtr->PersistData(executionOrder.GetProduct().GetProductId(), executionOrder);
    }

    void ProcessRemove(ExecutionOrder<Bond>& executionOrder) {}  // No implementation.
    void ProcessUpdate(ExecutionOrder<Bond>& executionOrder) {}  // No implementation.
};



#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALEXECUTIONSERVICELISTENER_HPP
