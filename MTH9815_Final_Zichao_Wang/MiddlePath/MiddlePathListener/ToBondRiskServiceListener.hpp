// ToBondRiskServiceListener.hpp
// Created by Zichao Wang
// Date: Dec 10, 2018

// data flow:
// BondPositionService --> ToBondRiskServiceListener --> BondRiskService


#ifndef TOBONDRISKSERVICELISTENER_HPP
#define TOBONDRISKSERVICELISTENER_HPP


#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathService/BondPositionService.hpp"
#include "MiddlePath/MiddlePathService/BondRiskService.hpp"
#include "MiddlePath/MiddlePathGeneral/riskservice.hpp"
#include "MiddlePath/MiddlePathGeneral/tradebookingservice.hpp"

#include <iostream>


class ToBondRiskServiceListener : public ServiceListener<Position<Bond> >
{
private:
	// service it wants to pass data to
	BondRiskService * bondRiskServicePtr;

public:
	// ctor
	ToBondRiskServiceListener(BondRiskService* _bondRiskServicePtr) : bondRiskServicePtr(_bondRiskServicePtr) {}

	void ProcessAdd(Position<Bond>& position)
	{
		//std::cout << "to bond risk service listener receives: ";
		//position.Print();
		//std::cout << std::endl;

		bondRiskServicePtr->UpdatePosition(position);
	}

	void ProcessRemove(Position<Bond>& position) {}  // No implementation.
	void ProcessUpdate(Position<Bond>& position) {}  // No implementation.

};


#endif // !TOBONDRISKSERVICELISTENER_HPP

