//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALINQUIRYSERVICECONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALINQUIRYSERVICECONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "Foundation/soa.hpp"
#include "InquiryPart/InquiryPartGeneral/inquiryservice.hpp"
#include "BondInfoHelper.hpp"

// data flow:
// BondHistoricalInquiryService --> BondHistoricalInquiryServiceConnector --> inquiry_results.txt


class BondHistoricalInquiryServiceConnector : public Connector<Inquiry<Bond> >
{
public:
    // ctor
    BondHistoricalInquiryServiceConnector() = default;

    // Write a position into positions.txt.
    void Publish(Inquiry<Bond>& inquiry);

    void Subscribe() {}  // No implementation.
};

void BondHistoricalInquiryServiceConnector::Publish(Inquiry<Bond>& inquiry)
{
    std::string inquiryState;
    switch(inquiry.GetState())
    {
        case RECEIVED : inquiryState = "RECEIVED"; break;
        case QUOTED : inquiryState = "QUOTED"; break;
        case DONE : inquiryState = "DONE"; break;
        case REJECTED : inquiryState = "REJECTED"; break;
        case CUSTOMER_REJECTED : inquiryState = "CUSTOMER_REJECTED";
    }

    std::ofstream f;
    f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\inquiry_results.txt", ios::app);

    if (f.is_open())
    {
        f << "Inquiry ID: " << inquiry.GetInquiryId()
          << ", CUSIP: " << inquiry.GetProduct().GetProductId()
          << ", price: " << PriceToPriceString(inquiry.GetPrice())
          << ", side: " << (inquiry.GetSide() == BUY ? "buy" : "sell")
          << ", quantity: " << inquiry.GetQuantity()
          << ", state: " << inquiryState
          << std::endl;
    }
    else
    {
        std::cout << "Cannot open inquiry_results.txt." << std::endl;
        exit(-1);
    }
    f.close();
}


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALINQUIRYSERVICECONNECTOR_HPP
