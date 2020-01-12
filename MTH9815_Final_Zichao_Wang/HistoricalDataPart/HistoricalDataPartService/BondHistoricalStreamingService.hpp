//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALSTREAMINGSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALSTREAMINGSERVICE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "LeftPath/LeftPathGeneral/streamingservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartGeneral/historicaldataservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalStreamingServiceConnector.hpp"

class BondHistoricalStreamingService : public HistoricalDataService<PriceStream<Bond> >
{
private:
    // listener pointer list
    std::vector<ServiceListener<PriceStream<Bond> >*> listenerPtrs;
    // K : CUSIP; V : price stream of this bond.
    std::map<std::string, PriceStream<Bond> > priceStreams;

    BondHistoricalStreamingServiceConnector* bondHistoricalStreamingServiceConnectorPtr;

public:
    // ctor
    BondHistoricalStreamingService(BondHistoricalStreamingServiceConnector* _bondHistoricalStreamingServiceConnectorPtr) : bondHistoricalStreamingServiceConnectorPtr(_bondHistoricalStreamingServiceConnectorPtr) {}

    // Given CUSIP, get price stream of this bond.
    PriceStream<Bond>& GetData(std::string CUSIP)
    {
        return priceStreams.at(CUSIP);
    }

    //No implementation.
    void OnMessage(PriceStream<Bond>& priceStream) {}

    // Add a listener pointer into pointer list.
    void AddListener(ServiceListener<PriceStream<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    // Get all listener pointers.
    const std::vector<ServiceListener<PriceStream<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    // Publish price stream into streaming.txt by invoking Connector::Publish().
    void PersistData(std::string CUSIP, PriceStream<Bond>& priceStream)
    {
        bondHistoricalStreamingServiceConnectorPtr->Publish(priceStream);
    }

};


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALSTREAMINGSERVICE_HPP
