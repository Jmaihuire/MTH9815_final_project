// BondAlgoStreamingService.hpp
// Created by Zichao Wang
// Date: Dec 8, 2018

#ifndef BONDALGOSTREAMINGSERVICE_HPP
#define BONDALGOSTREAMINGSERVICE_HPP

#include <map>
#include <vector>
#include <string>
#include <utility>  // std::pair

#include "../../Foundation/soa.hpp"
#include "../../Foundation/products.hpp"
#include "../LeftPathGeneral/streamingservice.hpp"


// K type : CUSIP
// V type : algo stream of this bond
class BondAlgoStreamingService : public Service<string, AlgoStream>
{
private:
	std::map<string, AlgoStream> algoStreams;  // 6 pairs
	std::vector<ServiceListener<AlgoStream>*> listenerPtrs;  // listener list

public:
	// ctor
	BondAlgoStreamingService() {}

	// copy ctor
	BondAlgoStreamingService(const BondAlgoStreamingService& _bondAlgoStreamingService)
	{
		algoStreams = _bondAlgoStreamingService.GetAlgoStreams();
		listenerPtrs = _bondAlgoStreamingService.GetListeners();
	}

	// dtor
	~BondAlgoStreamingService() {}

	// assignment operator
	BondAlgoStreamingService& operator =(const BondAlgoStreamingService& _bondAlgoStreamingService)
	{
		algoStreams = _bondAlgoStreamingService.GetAlgoStreams();
		listenerPtrs = _bondAlgoStreamingService.GetListeners();
		return *this;
	}

	// Get algo streams and listener pointer list.
	const std::map<string, AlgoStream> GetAlgoStreams() const
	{
		return algoStreams;
	}

	const std::vector<ServiceListener<AlgoStream>*>& GetListeners() const
	{
		return listenerPtrs;
	}

	// Set algo streams, pricing and listener pointer list.
	void SetAlgoStreams(const std::map<string, AlgoStream>& _algoStreams)
	{
		algoStreams = _algoStreams;
	}

	void SetListenerPtrs(const std::vector<ServiceListener<AlgoStream>*>& _listenerPtrs)
	{
		listenerPtrs = _listenerPtrs;
	}


	AlgoStream& GetData(string productId)
	{
		return algoStreams.at(productId);
	}

	void AddListener(ServiceListener<AlgoStream>* listenerPtr)
	{
		listenerPtrs.push_back(listenerPtr);
		//std::cout << "Added listener on bond algo streaming service." << std::endl;
	}

	// No implementation, since we do not want to read data via connectors.
	void OnMessage(AlgoStream& data) {}

	// Update or add algo stream according to a new price,
	// and notify all listeners.
	void AddAlgoStream(Price<Bond>& price);

	// Print bond algo streaming service.
	//void Print() const;

};


void BondAlgoStreamingService::AddAlgoStream(Price<Bond>& price)
{
	// Always fetch CUSIP first.
	std::string CUSIP = price.GetProduct().GetProductId();
	
	auto iterator = algoStreams.find(CUSIP);
	AlgoStream* agsPtr = nullptr;

	// If this CUSIP exists in hash table.
	if (iterator != algoStreams.end())
	{
		agsPtr = &(iterator->second);
		agsPtr->UpdatePriceStream(price);
		//std::cout << "bond algo streaming service has: ";
		//algoStreams[CUSIP].Print();
		//std::cout << std::endl;
	}
	// If it is a new CUSIP, create a new algo stream
	// according to this price and add it into hash table.
	else
	{
		//agsPtr = new AlgoStream(price);
		//std::cout << "*agsPtr: ";
		//(*agsPtr).Print();
		//std::cout << std::endl;
		//algoStreams.insert(std::pair<string, AlgoStream>(CUSIP, *agsPtr));
		algoStreams.insert(std::pair<string, AlgoStream>(CUSIP, AlgoStream(price)));
		agsPtr = &(algoStreams[CUSIP]);
		//std::cout << "bond algo streaming service has: ";
		//algoStreams[CUSIP].Print();
		//std::cout << std::endl;
	}

	// notify its listeners.
	//std::cout << "Bond algo streaming service notifying all listeners..." << std::endl;
	for (auto listenerPtr : listenerPtrs)
		listenerPtr->ProcessAdd(*agsPtr);
	//std::cout << "Bond algo streaming service has notified all listeners." << std::endl;
}

/*
void BondAlgoStreamingService::Print()
{
	// Print 6 pairs in hash table respectively.
	std::string s1 = "9128285Q9";
	std::string s2 = "9128285L0";
	std::string s3 = "9128285P1";
	std::string s4 = "9128285N6";
	std::string s5 = "9128285M8";
	std::string s6 = "912810SE9";

	algoStreams[s1].Print(); std::cout << std::endl;
	algoStreams[s2].Print(); std::cout << std::endl;
	algoStreams[s3].Print(); std::cout << std::endl;
	algoStreams[s4].Print(); std::cout << std::endl;;
	algoStreams[s5].Print(); std::cout << std::endl;
	algoStreams[s6].Print(); std::cout << std::endl;
}
*/


#endif // !BONDALGOSTREAMINGSERVICE_HPP

