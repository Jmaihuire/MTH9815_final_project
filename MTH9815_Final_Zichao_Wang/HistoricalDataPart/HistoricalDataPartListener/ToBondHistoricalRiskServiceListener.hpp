//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALRISKSERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALRISKSERVICELISTENER_HPP


// data flow:
// BondRiskService --> ToBondHistoricalRiskServiceListener --> BondHistoricalRiskService


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/riskservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalRiskService.hpp"


class ToBondHistoricalRiskServiceListener : public ServiceListener<PV01<Bond> >
{
private:
    BondHistoricalRiskService* bondHistoricalRiskServicePtr;

public:
    // ctor
    ToBondHistoricalRiskServiceListener(BondHistoricalRiskService* _bondHistoricalRiskServicePtr) : bondHistoricalRiskServicePtr(_bondHistoricalRiskServicePtr) {}

    void ProcessAdd(PV01<Bond>& pv01)
    {
        //std::cout << "ToBondHistoricalRiskServiceListener has: ";
        //pv01.Print();
        //std::cout << std::endl;

        bondHistoricalRiskServicePtr->OnMessage(pv01);
        // Publish position data.
        bondHistoricalRiskServicePtr->PersistData(pv01.GetProduct().GetProductId(), pv01);
    }

    void ProcessRemove(PV01<Bond>& pv01) {}  // No implementation.
    void ProcessUpdate(PV01<Bond>& pv01) {}  // No implementation.
};

#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALRISKSERVICELISTENER_HPP
