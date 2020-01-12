//
// Created by Zichao Wang on 2018/12/14.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALPOSITIONSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALPOSITIONSERVICE_HPP


#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/positionservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartGeneral/historicaldataservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalPositionServiceConnector.hpp"


class BondHistoricalPositionService : public HistoricalDataService<Position<Bond> >
{
private:
    // listener pointer list
    std::vector<ServiceListener<Position<Bond> >*> listenerPtrs;
    // K : CUSIP; V : position of this bond.
    std::map<std::string, Position<Bond> > positions;

    BondHistoricalPositionServiceConnector* bondHistoricalPositionServiceConnectorPtr;

public:
    // ctor
    BondHistoricalPositionService(BondHistoricalPositionServiceConnector* _bondHistoricalPositionServiceConnectorPtr) : bondHistoricalPositionServiceConnectorPtr(_bondHistoricalPositionServiceConnectorPtr) {}

    // Given CUSIP, get position of this bond.
    Position<Bond>& GetData(std::string CUSIP)
    {
        return positions.at(CUSIP);
    }

    // Update position and notify all listeners.
    // Create position if it is a new CUSIP.
    void OnMessage(Position<Bond>& position)
    {
        std::string CUSIP = position.GetProduct().GetProductId();
        positions[CUSIP] = position;

        for(auto& listenerPtr : listenerPtrs)
            listenerPtr->ProcessAdd(position);
    }

    // Add a listener pointer into pointer list.
    void AddListener(ServiceListener<Position<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    // Get all listener pointers.
    const std::vector<ServiceListener<Position<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    // Publish position into positions.txt by invoking Connector::Publish().
    void PersistData(std::string CUSIP, Position<Bond>& position)
    {
        bondHistoricalPositionServiceConnectorPtr->Publish(position);
    }

};



#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALPOSITIONSERVICE_HPP
