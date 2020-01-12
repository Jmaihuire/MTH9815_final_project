// BondRiskService.hpp
// Created by Zichao Wang
// Date: Dec 10, 2018

#ifndef BONDRISKSERVICE_HPP
#define BONDRISKSERVICE_HPP


#include "MiddlePath/MiddlePathGeneral/riskservice.hpp"
#include "MiddlePath/MiddlePathGeneral/positionservice.hpp"
#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"

#include <vector>
#include <map>
#include <iostream>
#include <utility>


class BondRiskService : public RiskService<Bond>
{
private:
	std::vector<ServiceListener<PV01<Bond> >*> listenerPtrs;
	// K : CUSIP
	// V : its pv01 value.
	std::map<std::string, PV01<Bond> > risks;

public:
	// ctor
	BondRiskService() = default;

	// Get pv01 from CUSIP.
	PV01<Bond>& GetData(std::string CUSIP)
	{
		return risks.at(CUSIP);
	}

	void OnMessage(PV01<Bond>& pv01) {}  // No implementation.

	// Add a listener pointer.
	void AddListener(ServiceListener<PV01<Bond> >* listenerPtr)
	{
		listenerPtrs.push_back(listenerPtr);
	}

	// Get listener pointer list.
	const std::vector<ServiceListener<PV01<Bond> >*>& GetListeners() const
	{
		return listenerPtrs;
	}

	// Add a particular bond position into hash table,
	// and notify listeners.
	void UpdatePosition(Position<Bond>& position);

	// Get pv01 for given bucket of securities.
	/*
	double GetBucketedRisk(const BucketedSector<Bond>& bucketedSector) const
	{
		double sectoredPV01 = 0;
		for (auto& bond : bucketedSector.GetProducts())
			sectoredPV01 += risks.at(bond.GetProductId()).GetPV01();

		return sectoredPV01;
	}
	 */

};

void BondRiskService::UpdatePosition(Position<Bond>& position)
{
	Bond bond = position.GetProduct();
	std::string CUSIP = bond.GetProductId();
	long quantity = position.GetAggregatePosition();

	PV01<Bond>* pv01Ptr;
	auto iterator = risks.find(CUSIP);

	// If this bond already exists in hash table,
	// just update its quantity.
	if (iterator != risks.end())
	{
		pv01Ptr = &(iterator->second);
		pv01Ptr->AddQuantity(position.GetAggregatePosition() - pv01Ptr->GetQuantity());

		//std::cout << "bond risk service has: ";
		//risks.at(CUSIP).Print();
		//std::cout << std::endl;
	}
	// Otherwise create a new pair and insert it into hash table.
	else
	{
		PV01<Bond> pv01(bond);
		pv01.AddQuantity(quantity);
		risks.insert(std::pair<std::string, PV01<Bond> >(CUSIP, pv01));

		//std::cout << "bond risk service has: ";
		//risks.at(CUSIP).Print();
		//std::cout << std::endl;

		pv01Ptr = &(risks[CUSIP]);
	}

	//std::cout << "*pv01ptr: ";
	//(*pv01Ptr).Print();
	//std::cout << std::endl;

	// Notify all listeners.
	for (auto & listenerPtr : listenerPtrs)
		listenerPtr->ProcessAdd(*pv01Ptr);

}


#endif // !BONDRISKSERVICE_HPP
