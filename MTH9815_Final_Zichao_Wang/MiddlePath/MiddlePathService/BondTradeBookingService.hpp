// BondTradeBookService.hpp
// Created by Zichao Wang
// Date: Dec9, 2018


#ifndef BONDTRADEBOOKSERVICE_HPP
#define BONDTRADEBOOKSERVICE_HPP

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/tradebookingservice.hpp"

#include <vector>
#include <map>


class BondTradeBookingService : public TradeBookingService<Bond>
{
private:
	// listener pointer list and trade hash map
	std::vector<ServiceListener<Trade<Bond> >*> listenerPtrs;
	// key: trade id; value : bond trade
	std::map<std::string, Trade<Bond> > trades;

public:
	// ctor
	BondTradeBookingService() = default;

	// Get trade using trade id.
	Trade<Bond>& GetData(std::string tradeId)
	{
		return trades.at(tradeId);
	}

	// Call BookTrade() function.
	void OnMessage(Trade<Bond>& trade)
	{
		BookTrade(trade);
	}

	// Add a listener pointer to the list.
	void AddListener(ServiceListener<Trade<Bond> >* listenerPtr)
	{
		listenerPtrs.push_back(listenerPtr);
	}

	// Get all listener pointers.
	const std::vector<ServiceListener<Trade<Bond> >*>& GetListeners() const
	{
		return listenerPtrs;
	}

	// Add trade into hash table, and notify all listeners.
	void BookTrade(Trade<Bond>& trade)
	{
		trades[trade.GetTradeId()] = trade;

		//std::cout << "bond trade booking service has: ";
		//trades[trade.GetTradeId()].Print();
		//std::cout << std::endl;

		for (auto listenerPtr : listenerPtrs)
			listenerPtr->ProcessAdd(trade);
	}

};


#endif // !BONDTRADEBOOKSERVICE_HPP

