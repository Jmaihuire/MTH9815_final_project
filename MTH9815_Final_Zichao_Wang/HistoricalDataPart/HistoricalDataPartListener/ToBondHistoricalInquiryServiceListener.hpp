//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALINQUIRYSERVICELISTENER_HPP
#define MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALINQUIRYSERVICELISTENER_HPP

// data flow:
// BondInquiryService --> ToBondHistoricalInquiryServiceListener --> BondHistoricalInquiryService


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "InquiryPart/InquiryPartGeneral/inquiryservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalInquiryService.hpp"


class ToBondHistoricalInquiryServiceListener : public ServiceListener<Inquiry<Bond> >
{
private:
    BondHistoricalInquiryService* bondHistoricalInquiryServicePtr;

public:
    // ctor
    ToBondHistoricalInquiryServiceListener(BondHistoricalInquiryService* _bondHistoricalInquiryServicePtr) : bondHistoricalInquiryServicePtr(_bondHistoricalInquiryServicePtr) {}

    void ProcessAdd(Inquiry<Bond>& inquiry)
    {
        // Notify inquiry service.
        bondHistoricalInquiryServicePtr->OnMessage(inquiry);

        // Publish price stream data.
        bondHistoricalInquiryServicePtr->PersistData(inquiry.GetInquiryId(), inquiry);
    }

    void ProcessRemove(Inquiry<Bond>& inquiry) {}  // No implementation.
    void ProcessUpdate(Inquiry<Bond>& inquiry) {}  // No implementation.
};


#endif //MTH9815_FINAL_ZICHAO_WANG_TOBONDHISTORICALINQUIRYSERVICELISTENER_HPP
