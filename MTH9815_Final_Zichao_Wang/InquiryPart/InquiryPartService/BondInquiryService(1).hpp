//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDINQUIRYSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDINQUIRYSERVICE_HPP

#include "InquiryPart/InquiryPartGeneral/inquiryservice.hpp"
#include "Foundation/products.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>


class BondInquiryService: public InquiryService<Bond>
{
private:
    std::vector<ServiceListener<Inquiry<Bond> >*> listenerPtrs;
    std::map<std::string, Inquiry<Bond> > inquiries;

public:
    // ctor
    BondInquiryService() = default;

    Inquiry<Bond>& GetData(std::string inquiryID)
    {
        return inquiries.at(inquiryID);
    }

    void OnMessage(Inquiry<Bond> & inquiry)
    {
        inquiry.SetInquiry(inquiry.GetPrice(), DONE);
        inquiries[inquiry.GetInquiryId()] = inquiry;

        for(auto & listenerPtr : listenerPtrs)
            listenerPtr->ProcessAdd(inquiry);
    }

    void AddListener(ServiceListener<Inquiry<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    const std::vector<ServiceListener<Inquiry<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    void SendQuote(const std::string & inquiryID, double price) {}
    void RejectInquiry(const std::string & inquiryID) {}
};


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDINQUIRYSERVICE_HPP
