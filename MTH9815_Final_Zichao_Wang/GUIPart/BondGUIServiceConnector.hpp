//
// Created by Zichao Wang on 2018/12/22.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDGUISERVICECONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDGUISERVICECONNECTOR_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "Foundation/soa.hpp"
#include "LeftPath/LeftPathGeneral/pricingservice.hpp"
#include "BondInfoHelper.hpp"

// data flow:
// BondGUIService --> BondGUIServiceConnector --> gui.txt


class BondGUIServiceConnector : public Connector<Price<Bond> >
{
public:
    // ctor
    BondGUIServiceConnector() = default;

    // Write a price into gui.txt.
    void Publish(Price<Bond>& price);

    void Subscribe() {}  // No implementation.
};

void BondGUIServiceConnector::Publish(Price<Bond>& price)
{
    // From price fetch CUSIP, bid and offer order.
    std::string CUSIP = price.GetProduct().GetProductId();

    std::ofstream f;
    f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\gui.txt", ios::app);

    if (f.is_open())
    {
        f << "CUSIP: " << CUSIP
          << ", mid price: " << price.GetMid()
          << ", spread: " << price.GetBidOfferSpread() << ", time stamp: ";

        std::time_t result = std::time(nullptr);
        f << std::asctime(std::localtime(&result))
                  << result << ".";
        f << std::endl;
    }
    else
    {
        std::cout << "Cannot open or create gui.txt." << std::endl;
        exit(-1);
    }
    f.close();
}


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDGUISERVICECONNECTOR_HPP
