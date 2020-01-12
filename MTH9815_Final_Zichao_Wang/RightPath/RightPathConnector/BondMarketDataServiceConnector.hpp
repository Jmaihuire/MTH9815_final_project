//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDMARKETDATASERVICECONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDMARKETDATASERVICECONNECTOR_HPP

#include "BondInfoHelper.hpp"
#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "RightPath/RightPathService/BondMarketDataService.hpp"

#include <string>
#include <fstream>


class BondMarketDataServiceConnector : public Connector<OrderBook<Bond> >
{
private:
    BondMarketDataService* bondMarketDataServicePtr;

public:
    // ctor
    BondMarketDataServiceConnector(BondMarketDataService* _bondMarketDataServicePtr) : bondMarketDataServicePtr(_bondMarketDataServicePtr) {}

    void Publish(OrderBook<Bond>& orderBook) {}  // No implementation.

    // Read market data from "marketdata.txt".
    void Subscribe(std::string filePath);

};

void BondMarketDataServiceConnector::Subscribe(std::string filePath)
{
    std::ifstream f;
    f.open(filePath);

    // If open successfully, just read data line by line.
    if(f.is_open())
    {
        // substr[0] : CUSIP
        // substr[1] : mid price
        // substr[2] : spread / (1/128)
        std::string substr[3];
        std::string line;

        // Read each line.
        while (std::getline(f, line))
        {
            std::stringstream lineStream(line);
            for (int i = 0; i < 2; i++)
                std::getline(lineStream, substr[i], ',');
            std::getline(lineStream, substr[2]);

            // Transform data.
            boost::gregorian::date *maturityPtr;
            int CUSIPIndex = CUSIPToIndex(substr[0]);
            switch (CUSIPIndex) {
                case 0:
                    maturityPtr = new boost::gregorian::date(2020, Dec, 8);
                    break;
                case 1:
                    maturityPtr = new boost::gregorian::date(2021, Dec, 8);
                    break;
                case 2:
                    maturityPtr = new boost::gregorian::date(2023, Dec, 8);
                    break;
                case 3:
                    maturityPtr = new boost::gregorian::date(2025, Dec, 8);
                    break;
                case 4:
                    maturityPtr = new boost::gregorian::date(2028, Dec, 8);
                    break;
                default:
                    maturityPtr = new boost::gregorian::date(2048, Dec, 8);
                    break;
            }

            Bond bond(substr[0], CUSIP, "T", 0.15, *maturityPtr);

            int digitPartLength = substr[1].size();
            if (substr[1][digitPartLength - 1] == '+')
                substr[1][digitPartLength - 1] = '4';
            double midPrice = CalculatePrice(substr[1]);
            double spread = 1.0 / 128 * std::stol(substr[2]);

            std::multiset<Order> bidSide;
            std::multiset<Order> offerSide;

            // Just assume for simplicity that every two
            // adjacent orders have 1/128 difference in price on both sides.
            for (int i = 0; i < 5; i++) {
                Order bidOrder(midPrice + 0.5 * spread + i * 1.0 / 128, (5 - i) * 10000000, BID);
                Order offerOrder(midPrice - 0.5 * spread - i * 1.0 / 128, (5 - i) * 10000000, OFFER);
                bidSide.insert(bidOrder);
                offerSide.insert(offerOrder);
            }

            OrderBook<Bond> orderBook(bond, bidSide, offerSide);

            //std::cout << "Order book which bond market data service connector receives: ";
            //orderBook.Print();
            //std::cout << std::endl;

            bondMarketDataServicePtr->OnMessage(orderBook);
        }
    }
    else
    {
        std::cout << "Cannot open marketdata.txt." << std::endl;
        exit(-1);
    }
}



#endif //MTH9815_FINAL_ZICHAO_WANG_BONDMARKETDATASERVICECONNECTOR_HPP
