// BondPricingConncector.hpp
// Created by Zichao Wang
// Date: Dec 8, 2018

// data flow:
// prices.txt --> BondPricingServiceConnector --> BondPricingService


#ifndef BONDPRICINGSERVICECONNECTOR_HPP
#define BONDPRICINGSERVICECONNECTOR_HPP

#include <string>
#include <fstream>

#include "../../Foundation/soa.hpp"
#include "../../BondInfoHelper.hpp"
#include "../LeftPathGeneral/pricingservice.hpp"
#include "../LeftPathService/BondPricingService.hpp"
#include "../../Foundation/products.hpp"


// We want to subscribe bond price info.
class BondPricingServiceConnector : public Connector<Price<Bond> >
{
private:
	// service it wants to connect with
	BondPricingService* bondPricingServicePtr;

public:
	// ctor
	BondPricingServiceConnector(BondPricingService* _bondPricingServicePtr) : bondPricingServicePtr(_bondPricingServicePtr) {}

	// Subscribe (i.e., Read) all prices from "prices.txt".
	// and call Service.OnMessage() to pass down the new info.
	void Subscribe(std::string filePath)
	{
		std::ifstream f;
		f.open(filePath);
		
		// If open successfully, read data.
		if (f.is_open())
		{
			// substr:
			// substr[0] : CUSIP
			// substr[1] : price string
			// substr[2] : spread index (1 or 2)
			std::string substr[3];

			std::string line;  // Store one line of data.

			while (std::getline(f, line))  // Read each line.
			{
				std::stringstream lineStream(line);
				for (int i = 0; i < 2; i++)
					std::getline(lineStream, substr[i], ',');
				std::getline(lineStream, substr[2]);

				// Transform data.
				int digitPartLength = substr[1].size();
				if (substr[1][digitPartLength - 1] == '+')
					substr[1][digitPartLength - 1] = '4';

				double price = CalculatePrice(substr[1]);
				double spread = (double)(substr[2][0] - '0') / 128.0;

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
				Price<Bond> bondPriceObject(bond, price, spread);
				//std::cout << "Input data from bond pricing connector: ";
				//bondPriceObject.Print();
				//std::cout << std::endl;

				// For each price, call Service.OnMessage() once to pass this piece of data.
				bondPricingServicePtr->OnMessage(bondPriceObject);
			}
			f.close();
		}
		else  // Otherwise report error and exit.
		{
			std::cout << "Cannot open prices.txt." << std::endl;
			exit(-1);
		}
	}

	// We do not need to implement Publish() method.
	virtual void Publish(Price<Bond>& data) {}

};


#endif // !BONDPRICINGSERVICECONNECTOR_HPP

