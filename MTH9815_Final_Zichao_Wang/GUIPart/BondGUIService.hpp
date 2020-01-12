//
// Created by Zichao Wang on 2018/12/22.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDGUISERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDGUISERVICE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "LeftPath/LeftPathGeneral/pricingservice.hpp"
#include "GUIPart/BondGUIServiceConnector.hpp"

class BondGUIService : public Service<std::string, Price<Bond> >
{
private:
    // listener pointer list
    std::vector<ServiceListener<Price<Bond> >*> listenerPtrs;
    // K : CUSIP; V : price of this bond.
    std::map<std::string, Price<Bond> > prices;

    BondGUIServiceConnector* bondGUIServiceConnectorPtr;

public:
    // ctor
    BondGUIService(BondGUIServiceConnector* _bondGUIServiceConnectorPtr) : bondGUIServiceConnectorPtr(_bondGUIServiceConnectorPtr) {}

    // Given CUSIP, get price of this bond.
    Price<Bond>& GetData(std::string cusip)
    {
        return prices.at(cusip);
    }

    //No implementation.
    void OnMessage(Price<Bond>& price) {}

    // Add a listener pointer into pointer list.
    void AddListener(ServiceListener<Price<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    // Get all listener pointers.
    const std::vector<ServiceListener<Price<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    // Publish price into gui.txt by invoking Connector::Publish().
    void PersistData(std::string cusip, Price<Bond>& price)
    {
        bondGUIServiceConnectorPtr->Publish(price);
    }

};


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDGUISERVICE_HPP
