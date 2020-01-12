//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALINQUIRYSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALINQUIRYSERVICE_HPP

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "InquiryPart/InquiryPartGeneral/inquiryservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartGeneral/historicaldataservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalInquiryServiceConnector.hpp"

class BondHistoricalInquiryService : public HistoricalDataService<Inquiry<Bond> >
{
private:
    // listener pointer list
    std::vector<ServiceListener<Inquiry<Bond> >*> listenerPtrs;
    // K : CUSIP; V : price stream of this bond.
    std::map<std::string, Inquiry<Bond> > inquiries;

    BondHistoricalInquiryServiceConnector* bondHistoricalInquiryServiceConnectorPtr;

public:
    // ctor
    BondHistoricalInquiryService(BondHistoricalInquiryServiceConnector* _bondHistoricalInquiryServiceConnectorPtr) : bondHistoricalInquiryServiceConnectorPtr(_bondHistoricalInquiryServiceConnectorPtr) {}

    // Given inquiry ID, get inquiry result.
    Inquiry<Bond>& GetData(std::string inquiryID)
    {
        return inquiries.at(inquiryID);
    }

    void OnMessage(Inquiry<Bond>& inquiry)
    {
        std::string inquiryID = inquiry.GetInquiryId();
        inquiries[inquiryID] = inquiry;

        for(auto & listenerPtr : listenerPtrs)
            listenerPtr->ProcessAdd(inquiry);
    }

    // Add a listener pointer into pointer list.
    void AddListener(ServiceListener<Inquiry<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    // Get all listener pointers.
    const std::vector<ServiceListener<Inquiry<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    // Publish price stream into streaming.txt by invoking Connector::Publish().
    void PersistData(std::string inquiryID, Inquiry<Bond>& inquiry)
    {
        bondHistoricalInquiryServiceConnectorPtr->Publish(inquiry);
    }

};


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALINQUIRYSERVICE_HPP
