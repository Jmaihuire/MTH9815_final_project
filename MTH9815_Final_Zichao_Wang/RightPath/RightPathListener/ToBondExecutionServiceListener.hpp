//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDEXECUTIONSERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDEXECUTIONSERVICELISTENER_HPP


// data flow:
// BondAlgoExecutionService --> ToBondExecutionServiceListener --> BondExecutionService


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathGeneral/marketdataservice.hpp"
#include "RightPath/RightPathGeneral/executionservice.hpp"
#include "RightPath/RightPathService/BondExecutionService.hpp"


class ToBondExecutionServiceListener : public ServiceListener<AlgoExecution>
{
private:
    BondExecutionService* bondExecutionServicePtr;

public:
    // ctor
    ToBondExecutionServiceListener(BondExecutionService* _bondExecutionServicePtr) : bondExecutionServicePtr(_bondExecutionServicePtr) {}

    void ProcessAdd(AlgoExecution& algoExecution)
    {
        //std::cout << "to bond execution service listener has: ";
        //algoExecution.GetExecutionOrder().Print();
        //std::cout << std::endl;

        ExecutionOrder<Bond> executionOrder = algoExecution.GetExecutionOrder();
        bondExecutionServicePtr->AddAlgoExecution(algoExecution);
        bondExecutionServicePtr->ExecuteOrder(executionOrder, CME);
    }

    void ProcessRemove(AlgoExecution& algoExecution) {}  // No implementation.

    void ProcessUpdate(AlgoExecution& algoExecution) {}  // No implementation.
};


#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDEXECUTIONSERVICELISTENER_HPP
