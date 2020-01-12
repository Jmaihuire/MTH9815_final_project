// BondPositionService.hpp
// Created by Zichao Wang
// Date: Dec 10, 2018


#ifndef BONDPOSITIONSERVICE_HPP
#define BONDPOSITIONSERVICE_HPP

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/positionservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalPositionServiceListener.hpp"

#include <vector>
#include <map>
#include <iostream>
#include <utility>


class BondPositionService : public PositionService<Bond>
{
private:
	// listener pointer list
	// listener to : (1) BondRiskService (2) BondHistoricalDataService
	std::vector<ServiceListener<Position<Bond> >*> listenerPtrs;
	// hash table
	// Key : CUSIP
	// Value : position of this bond
	std::map<std::string, Position<Bond> > positions;


public:
	// ctor
	BondPositionService() = default;

	// From CUSIP get bond position.
	Position<Bond>& GetData(std::string CUSIP)
	{
		return positions.at(CUSIP);
	}

	void OnMessage(Position<Bond>& position) {}  // No implementation.

	// Add a listener pointer.
	void AddListener(ServiceListener<Position<Bond> >* listenerPtr)
	{
		listenerPtrs.push_back(listenerPtr);
	}

	// Get listener pointer list.
	const std::vector<ServiceListener<Position<Bond> >*>& GetListeners() const
	{
		return listenerPtrs;
	}

	// Add a trade into its position hash table,
	// and notify all listeners.
	void BookTrade(const Trade<Bond>& trade);

};



void BondPositionService::BookTrade(const Trade<Bond>& trade)
{
	long quantity = trade.GetQuantity();
	if (trade.GetSide() == SELL)
		quantity = -quantity;
	Bond bond = trade.GetProduct();
	string CUSIP = bond.GetProductId();

	Position<Bond>* positionPtr;
	auto iterator = positions.find(CUSIP);

	// If CUSIP already exists in hash table, just update its position.
	if (iterator != positions.end())
	{
		positionPtr = &(iterator->second);
		positionPtr->AddPosition(trade.GetBook(), quantity);

		//std::cout << "bond position service has: ";
		//positions[CUSIP].Print();
		//std::cout << std::endl;
	}
	// Otherwise create position for this bond.
	else
	{
		Position<Bond> position(bond);
		position.AddPosition(trade.GetBook(), quantity);
		positions.insert(std::pair<std::string, Position<Bond> >(CUSIP, position));

		//std::cout << "bond position service has: ";
		//positions[CUSIP].Print();
		//std::cout << std::endl;

		positionPtr = &(positions[CUSIP]);

		/*
		Position<Bond> newPosition(bond);
		newPosition.AddPosition(trade.GetBook(), quantity);
		positions.insert(pair<string, Position<Bond> >(CUSIP, newPosition));
		positionPtr = &newPosition;
		*/


	}

	//std::cout << "*posistionPtr: ";
	//(*positionPtr).Print();
	//std::cout << std::endl;

	// Notify all listeners.
	for (auto& listenerPtr : listenerPtrs)
		listenerPtr->ProcessAdd(*positionPtr);
}


#endif // !BONDPOSITIONSERVICE_HPP

