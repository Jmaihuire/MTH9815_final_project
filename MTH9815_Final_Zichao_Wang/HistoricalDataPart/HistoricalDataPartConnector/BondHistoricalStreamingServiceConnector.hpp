//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALSTREAMINGSERVICECONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALSTREAMINGSERVICECONNECTOR_HPP


#include <iostream>
#include <fstream>
#include <string>

#include "Foundation/soa.hpp"
#include "LeftPath/LeftPathGeneral/streamingservice.hpp"
#include "BondInfoHelper.hpp"

// data flow:
// BondHistoricalStreamingService --> BondHistoricalStreamingServiceConnector --> streaming.txt


class BondHistoricalStreamingServiceConnector : public Connector<PriceStream<Bond> >
{
public:
    // ctor
    BondHistoricalStreamingServiceConnector() = default;

    // Write a position into positions.txt.
    void Publish(PriceStream<Bond>& priceStream);

    void Subscribe() {}  // No implementation.
};

void BondHistoricalStreamingServiceConnector::Publish(PriceStream<Bond>& priceStream)
{
    // From price stream fetch CUSIP, bid and offer order.
    std::string CUSIP = priceStream.GetProduct().GetProductId();
    auto bidOrder = priceStream.GetBidOrder();
    auto offerOrder = priceStream.GetOfferOrder();

    std::ofstream f;
    f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\streaming.txt", ios::app);

    if (f.is_open())
    {
        f << "CUSIP: " << CUSIP
          << "; side: " << (bidOrder.GetSide() == BID ? "bid" : "offer")
          << ", price: " << PriceToPriceString(bidOrder.GetPrice())
          << ", visible quantity: " << bidOrder.GetVisibleQuantity()
          << ", hidden quantity: " << bidOrder.GetHiddenQuantity()
          << "; side: " << (offerOrder.GetSide() == BID ? "bid" : "offer")
          << ", price: " << PriceToPriceString(offerOrder.GetPrice())
          << ", visible quantity: " << offerOrder.GetVisibleQuantity()
          << ", hidden quantity: " << offerOrder.GetHiddenQuantity()
          << std::endl;
    }
    else
    {
        std::cout << "Cannot open or create streaming.txt." << std::endl;
        exit(-1);
    }
    f.close();
}


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALSTREAMINGSERVICECONNECTOR_HPP
