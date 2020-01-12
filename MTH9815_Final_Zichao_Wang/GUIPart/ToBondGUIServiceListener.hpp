//
// Created by Zichao Wang on 2018/12/22.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDGUISERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDGUISERVICELISTENER_HPP

// data flow:
// BondPricingSvervice --> ToBondGUIServiceListener --> BondGUIService


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "LeftPath/LeftPathGeneral/pricingservice.hpp"
#include "GUIPart/BondGUIService.hpp"


class ToBondGUIServiceListener : public ServiceListener<Price<Bond> >
{
private:
    BondGUIService* bondGUIServicePtr;

public:
    // ctor
    ToBondGUIServiceListener(BondGUIService* _bondGUIServicePtr) : bondGUIServicePtr(_bondGUIServicePtr) {}

    void ProcessAdd(Price<Bond>& price)
    {
        // Publish price data.
        bondGUIServicePtr->PersistData(price.GetProduct().GetProductId(), price);
    }

    void ProcessRemove(Price<Bond>& priceStream) {}  // No implementation.
    void ProcessUpdate(Price<Bond>& priceStream) {}  // No implementation.
};


#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDGUISERVICELISTENER_HPP
