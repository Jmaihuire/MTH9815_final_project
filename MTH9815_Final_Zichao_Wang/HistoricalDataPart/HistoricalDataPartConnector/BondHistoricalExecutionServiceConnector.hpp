//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALEXECUTIONSERVICECONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALEXECUTIONSERVICECONNECTOR_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Foundation/soa.hpp"
#include "RightPath/RightPathGeneral/executionservice.hpp"
#include "BondInfoHelper.hpp"

// data flow:
// BondHistoricalExecutionService --> BondHistoricalExecutionServiceConnector --> executions.txt


class BondHistoricalExecutionServiceConnector : public Connector<ExecutionOrder<Bond> >
{
public:
    // ctor
    BondHistoricalExecutionServiceConnector() = default;

    // Write an execution order into executions.txt.
    void Publish(ExecutionOrder<Bond>& executionOrder);

    void Subscribe() {}  // No implementation.
};

void BondHistoricalExecutionServiceConnector::Publish(ExecutionOrder<Bond>& executionOrder)
{
    // From execution order fetch CUSIP.
    std::string cusip = executionOrder.GetProduct().GetProductId();

    std::ofstream f;
    f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\executions.txt", ios::app);

    if (f.is_open())
    {
        std::string orderType;
        switch(executionOrder.GetOrderType())
        {
            case FOK: orderType = "FOK"; break;
            case MARKET: orderType = "MARKET"; break;
            case LIMIT: orderType = "LIMIT"; break;
            case STOP: orderType = "STOP"; break;
            case IOC: orderType = "IOC"; break;
            default: orderType = "OTHER";
        }

        f << "CUSIP: " << cusip
          << ", side: " << (executionOrder.GetPricingSide() == BID ? "bid" : "offer")
          << ", order ID: " << executionOrder.GetOrderId()
          << ", order type: " << orderType
          << ", price: " << PriceToPriceString(executionOrder.GetPrice())
          << ", visible quantity: " << executionOrder.GetVisibleQuantity()
          << ", hidden quantity: " << executionOrder.GetHiddenQuantity()
          << ", parent order ID: " << executionOrder.GetParentOrderId()
          << ", is child order: " << std::boolalpha << executionOrder.IsChildOrder()
          << std::endl;
    }
    else
    {
        std::cout << "Cannot open or create executions.txt." << std::endl;
        exit(-1);
    }
    f.close();
}

#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALEXECUTIONSERVICECONNECTOR_HPP
