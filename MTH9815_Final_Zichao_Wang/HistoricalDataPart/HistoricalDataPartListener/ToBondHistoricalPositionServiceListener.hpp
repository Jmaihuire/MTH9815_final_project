//
// Created by Zichao Wang on 2018/12/14.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALPOSITIONSERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALPOSITIONSERVICELISTENER_HPP

// data flow:
// BondPositionService --> ToBondHistoricalPositionServiceListener --> BondHistoricalPositionService


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/positionservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalPositionService.hpp"


class ToBondHistoricalPositionServiceListener : public ServiceListener<Position<Bond> >
{
private:
    BondHistoricalPositionService* bondHistoricalPositionServicePtr;

public:
    // ctor
    ToBondHistoricalPositionServiceListener(BondHistoricalPositionService* _bondHistoricalPositionServicePtr) : bondHistoricalPositionServicePtr(_bondHistoricalPositionServicePtr) {}

    void ProcessAdd(Position<Bond>& position)
    {
        // Notify inquiry service.
        bondHistoricalPositionServicePtr->OnMessage(position);
        // Publish position data.
        bondHistoricalPositionServicePtr->PersistData(position.GetProduct().GetProductId(), position);
    }

    void ProcessRemove(Position<Bond>& position) {}  // No implementation.
    void ProcessUpdate(Position<Bond>& position) {}  // No implementation.
};


#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALPOSITIONSERVICELISTENER_HPP
