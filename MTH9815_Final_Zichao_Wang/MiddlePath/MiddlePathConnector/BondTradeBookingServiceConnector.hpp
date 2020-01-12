// BondTradeBookingServiceConnector.hpp
// Created by Zichao Wang
// Date: Dec 9, 2018

// data flow:
// trades.txt -->  BondTradeBookingServiceConnector --> BondTradeBookingService


#ifndef BONDTRADEBOOKINGSERVICECONNECTOR_HPP
#define BONDTRADEBOOKINGSERVICECONNECTOR_HPP

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/tradebookingservice.hpp"
#include "MiddlePath/MiddlePathService/BondTradeBookingService.hpp"
#include "BondInfoHelper.hpp"

#include <string>
#include <fstream>


class BondTradeBookingServiceConnector : public Connector<Trade<Bond> >
{
private:
	// service it wants to connect with
	BondTradeBookingService * bondTradeBookingServicePtr;

public:
	// ctor
	BondTradeBookingServiceConnector(BondTradeBookingService* _bondTradeBookingServicePtr) : bondTradeBookingServicePtr(_bondTradeBookingServicePtr) {}

	void Publish(Trade<Bond>& trade) {}  //No implementation.

	// Subscribe (i.e., Read) all trades from "trades.txt".
	// and call Service.OnMessage() to pass down the new info.
	void Subscribe(std::string filePath);
};


void BondTradeBookingServiceConnector::Subscribe(std::string filePath)
{
	std::ifstream f;
	//f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\trades.txt");
	f.open(filePath);

	// If open successfully, read data.
	if (f.is_open())
	{
		// substr[0] : CUSIP
		// substr[1] : trade id
		// substr[2] : trading book
		// substr[3] : price
		// substr[4] : quantity
		// substr[5] : side
		std::string substr[6];

		std::string line;  // Store one line of data.

		while (std::getline(f, line))  // Read each line.
		{
			std::stringstream lineStream(line);
			for (int i = 0; i < 5; i++)
				std::getline(lineStream, substr[i], ',');
			std::getline(lineStream, substr[5]);

			// Transform data.
			int digitPartLength = substr[3].size();
			if (substr[3][digitPartLength - 1] == '+')
				substr[3][digitPartLength - 1] = '4';
			double price = CalculatePrice(substr[3]);

			boost::gregorian::date * maturityPtr;
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
			Trade<Bond> trade(bond, substr[1], price, substr[2], std::stol(substr[4]), (substr[5] == "BUY" ? BUY : SELL));

			//std::cout << "Trade which bond trade booking service connector reads: ";
			//trade.Print();
			//std::cout << std::endl;

			bondTradeBookingServicePtr->OnMessage(trade);
		}
		f.close();
	}
	else  // Otherwise report error and exit.
	{
		std::cout << "Cannot open prices.txt." << std::endl;
		exit(-1);
	}

}


#endif // !BONDTRADEBOOKINGSERVICECONNECTOR_HPP

