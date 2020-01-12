//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALEXECUTIONSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALEXECUTIONSERVICE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathGeneral/executionservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartGeneral/historicaldataservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalExecutionServiceConnector.hpp"

class BondHistoricalExecutionService : public HistoricalDataService<ExecutionOrder<Bond> >
{
private:
    // listener pointer list
    std::vector<ServiceListener<ExecutionOrder<Bond> >*> listenerPtrs;
    // K : CUSIP; V : execution order of this bond.
    std::map<std::string, ExecutionOrder<Bond> > executionOrders;

    BondHistoricalExecutionServiceConnector* bondHistoricalExecutionServiceConnectorPtr;

public:
    // ctor
    BondHistoricalExecutionService(BondHistoricalExecutionServiceConnector* _bondHistoricalExecutionServiceConnectorPtr) : bondHistoricalExecutionServiceConnectorPtr(_bondHistoricalExecutionServiceConnectorPtr) {}

    // Given CUSIP, get execution order of this bond.
    ExecutionOrder<Bond>& GetData(std::string CUSIP)
    {
        return executionOrders.at(CUSIP);
    }

    //No implementation.
    void OnMessage(ExecutionOrder<Bond>& executionOrder) {}

    // Add a listener pointer into pointer list.
    void AddListener(ServiceListener<ExecutionOrder<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    // Get all listener pointers.
    const std::vector<ServiceListener<ExecutionOrder<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    // Publish execution order into executions.txt by invoking Connector::Publish().
    void PersistData(std::string CUSIP, ExecutionOrder<Bond>& executionOrder)
    {
        //std::cout << "bond execution historical service has: ";
        //executionOrder.Print();
        //std::cout << std::endl;

        bondHistoricalExecutionServiceConnectorPtr->Publish(executionOrder);
    }

};

#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALEXECUTIONSERVICE_HPP
