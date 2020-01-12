//
// Created by Zichao Wang on 2018/12/21.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDINQUIRYSERVICECONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDINQUIRYSERVICECONNECTOR_HPP

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "InquiryPart/InquiryPartService/BondInquiryService.hpp"
#include "BondInfoHelper.hpp"


class BondInquiryServiceConnector : public Connector<Inquiry<Bond> >
{
private:
    BondInquiryService* bondInquiryServicePtr;

public:
    // ctor
    BondInquiryServiceConnector(BondInquiryService* _bondInquiryServicePtr) : bondInquiryServicePtr(_bondInquiryServicePtr) {}

    void Publish(Inquiry<Bond>& inquiry) {}

    void Subscribe(std::string filePath);
};

void BondInquiryServiceConnector::Subscribe(std::string filePath)
{
    std::ifstream f;
    f.open(filePath);

    // If open successfully, read data.
    if (f.is_open())
    {
        // substr:
        // substr[0] : CUSIP
        // substr[1] : inquiry id
        // substr[2] : price string
        // substr[3] : quantity
        // substr[4] : side
        std::string substr[5];

        std::string line;  // Store one line of data.

        while (std::getline(f, line))  // Read each line.
        {
            std::stringstream lineStream(line);
            for (int i = 0; i < 4; i++)
                std::getline(lineStream, substr[i], ',');
            std::getline(lineStream, substr[4]);

            std::string inquiryID = substr[1];
            long quantity = std::stol(substr[3]);
            Side side = (substr[4] == "BUY" ? BUY : SELL);
            InquiryState inquiryState = RECEIVED;

            // Transform data.
            int digitPartLength = substr[2].size();
            if (substr[2][digitPartLength - 1] == '+')
                substr[2][digitPartLength - 1] = '4';
            double price = CalculatePrice(substr[2]);

            boost::gregorian::date* maturityPtr;
            int CUSIPIndex = CUSIPToIndex(substr[0]);
            switch (CUSIPIndex)
            {
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

            // Just assume all bonds have coupon rate 15% for simplicity.
            Bond bond(substr[0], CUSIP, "T", 0.15, *maturityPtr);

            Inquiry<Bond> inquiry(inquiryID, bond, side, quantity, price, inquiryState);

            bondInquiryServicePtr->SendQuote(inquiryID, price);
            inquiry.SetInquiry(100, RECEIVED);
            inquiry.SetInquiry(inquiry.GetPrice(), QUOTED);
            bondInquiryServicePtr->OnMessage(inquiry);
        }
        f.close();
    }
    else  // Otherwise report error and exit.
    {
        std::cout << "Cannot open prices.txt." << std::endl;
        exit(-1);
    }
}




#endif //MTH9815_FINAL_ZICHAO_WANG_BONDINQUIRYSERVICECONNECTOR_HPP
