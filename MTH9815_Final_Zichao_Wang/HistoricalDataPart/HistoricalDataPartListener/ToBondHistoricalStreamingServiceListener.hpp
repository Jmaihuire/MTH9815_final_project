//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALSTREAMINGSERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALSTREAMINGSERVICELISTENER_HPP

// data flow:
// BondStreamingService --> ToBondHistoricalStreamingServiceListener --> BondHistoricalStreamingService


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "LeftPath/LeftPathGeneral/streamingservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalStreamingService.hpp"


class ToBondHistoricalStreamingServiceListener : public ServiceListener<PriceStream<Bond> >
{
private:
    BondHistoricalStreamingService* bondHistoricalStreamingServicePtr;

public:
    // ctor
    ToBondHistoricalStreamingServiceListener(BondHistoricalStreamingService* _bondHistoricalStreamingServicePtr) : bondHistoricalStreamingServicePtr(_bondHistoricalStreamingServicePtr) {}

    void ProcessAdd(PriceStream<Bond>& priceStream)
    {
        // Publish price stream data.
        bondHistoricalStreamingServicePtr->PersistData(priceStream.GetProduct().GetProductId(), priceStream);
    }

    void ProcessRemove(PriceStream<Bond>& priceStream) {}  // No implementation.
    void ProcessUpdate(PriceStream<Bond>& priceStream) {}  // No implementation.
};


#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALSTREAMINGSERVICELISTENER_HPP
