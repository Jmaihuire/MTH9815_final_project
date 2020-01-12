// ToBondPositionServiceListener.hpp
// Created by Zichao Wang
// Date: Dec 10, 2018

// data flow:
// BondTradeBookingService --> ToBondPositionServiceListener --> BondPositionService


#ifndef TOBONDPOSITIONSERVICELISTENER_HPP
#define TOBONDPOSITIONSERVICELISTENER_HPP


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/tradebookingservice.hpp"
#include "MiddlePath/MiddlePathService/BondTradeBookingService.hpp"
#include "MiddlePath/MiddlePathService/BondPositionService.hpp"

#include <iostream>


class ToBondPositionServiceListener : public ServiceListener<Trade<Bond> >
{
private:
	// service it wants to pass data to
	BondPositionService * bondPositionServicePtr;

public:
	// ctor
	ToBondPositionServiceListener(BondPositionService* _bondPositionServicePtr) : bondPositionServicePtr(_bondPositionServicePtr) {}

	void ProcessAdd(Trade<Bond>& trade)
	{
		//std::cout << "to bond position service listener receives: ";
		//trade.Print();
		//std::cout << std::endl;
		bondPositionServicePtr->BookTrade(trade);
	}

	void ProcessRemove(Trade<Bond>& trade) {}  // No implementation.
	void ProcessUpdate(Trade<Bond>& trade) {}  // No implementation.

};


#endif // !TOBONDPOSITIONSERVICELISTENER_HPP

