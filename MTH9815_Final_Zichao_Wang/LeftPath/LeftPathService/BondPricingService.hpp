// BondPricingService.hpp
// Created by Zichao Wang
// Date: Dec 7, 2018


#ifndef BONDPRICINGSERVICE_HPP
#define BONDPRICINGSERVICE_HPP

#include <string>
#include <vector>
#include <map>

#include "../../Foundation/soa.hpp"
#include "../../Foundation/products.hpp"
#include "../LeftPathGeneral/pricingservice.hpp"
#include "../LeftPathGeneral/streamingservice.hpp"


// type K : CUSIP string; type V : bond price object.
class BondPricingService : public Service<string, Price<Bond> >
{
private:
	std::map<std::string, Price<Bond> > prices;  // hash table
	// listener pointer list
	std::vector <ServiceListener<Price<Bond> >*> listenerPtrs;

public:
	// ctor
	BondPricingService() {}

	BondPricingService(const BondPricingService& _bondPricingService)
	{
		prices = _bondPricingService.prices;
		listenerPtrs = _bondPricingService.listenerPtrs;
	}

	// Get bond price from hash table using a CUSIP.
	Price<Bond>& GetData(std::string CUSIP)
	{
		return prices.at(CUSIP);
	}

	// Read data from file via connector and notify listeners.
	void OnMessage(Price<Bond>& price);

	// Add a listener to listener list.
	void AddListener(ServiceListener<Price<Bond> >* listenerPtr)
	{
		listenerPtrs.push_back(listenerPtr);
		//std::cout << "Added listener on bond pricing service." << std::endl;
	}

	// Get listeners list.
	const std::vector<ServiceListener<Price<Bond> >*>& GetListeners() const
	{
		return listenerPtrs;
	}

	// Print the latest bond price of each maturity.
	//void Print() const;

};


void BondPricingService::OnMessage(Price<Bond>& price)
{
	// Insert price into hash table.
	prices[price.GetProduct().GetProductId()] = price;
	//std::cout << "bond pricing service has: ";
	//prices[price.GetProduct().GetProductId()].Print();
	//std::cout << std::endl;

	// Notify all listeners.
	//std::cout << "Bond pricing service notifying all listeners..." << std::endl;
	for (auto listenerPtr : listenerPtrs)
		listenerPtr->ProcessAdd(price);
	//std::cout << "Bond pricing service has notified all listeners." << std::endl;
}

/*
void BondPricingService::Print() const
{
	string s1 = "9128285Q9";
	string s2 = "9128285L0";
	string s3 = "9128285P1";
	string s4 = "9128285N6";
	string s5 = "9128285M8";
	string s6 = "912810SE9";

	prices[s1].Print(); cout << endl;
	prices[s2].Print(); cout << endl;
	prices[s3].Print(); cout << endl;
	prices[s4].Print(); cout << endl;
	prices[s5].Print(); cout << endl;
	prices[s6].Print(); cout << endl;
}
*/


#endif // !BONDPRICINGSERVICE_HPP


