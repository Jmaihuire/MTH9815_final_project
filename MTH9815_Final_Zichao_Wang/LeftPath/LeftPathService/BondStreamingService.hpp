// BondStreamingService.hpp
// Created by Zichao Wang
// Date: Dec 9, 2018


#ifndef BONDSTREAMINGSERVICE_HPP
#define BONDSTREAMINGSERVICE_HPP


#include "../../Foundation/soa.hpp"
#include "../../Foundation/products.hpp"
#include "../LeftPathGeneral/streamingservice.hpp"

#include <vector>
#include <map>
#include <string>


class BondStreamingService : public StreamingService<Bond>
{
private:
	// listener pointer list and internal hash table
	std::vector<ServiceListener<PriceStream<Bond> >*> listenerPtrs;
	std::map<std::string, PriceStream<Bond> > priceStreams;

public:
	// ctor
	BondStreamingService() = default;
	
	// Get price stream given CUSIP.
	PriceStream<Bond>& GetData(std::string CUSIP)
	{
		return priceStreams.at(CUSIP);
	}

	// Add and get listener pointers.
	void AddListener(ServiceListener<PriceStream<Bond> >* listenerPtr)
	{
		listenerPtrs.push_back(listenerPtr);
		//std::cout << "Added listener on bond streaming service." << std::endl;
	}

	const std::vector<ServiceListener<PriceStream<Bond> >*>& GetListeners() const
	{
		return listenerPtrs;
	}

	// Publish price streams via connector into a file.
	/*
	void PublishPrice(PriceStream<Bond>& priceStream)
	{
		bondStreamingServiceConnectorPtr->Publish(priceStream);
	}
	 */

	// We will not implement OnMessage() method.
	void OnMessage(PriceStream<Bond>& priceStream) {}

	// Transform algo stream into price stream, add it into
	// hash table, and notify listeners.
	void AddPriceStream(const AlgoStream& algoStream);

};

void BondStreamingService::AddPriceStream(const AlgoStream& algoStream)
{
	auto priceStream = algoStream.GetPriceStream();
	std::string CUSIP = priceStream.GetProduct().GetProductId();
	priceStreams[CUSIP] = priceStream;
	//std::cout << "bond streaming service has: ";
	//priceStreams[CUSIP].Print();
	//std::cout << std::endl;

	// Notify listeners.
	//std::cout << "Bond streaming service notifying all listeners..." << std::endl;
	for (auto& listenerPtr : listenerPtrs)
		listenerPtr->ProcessAdd(priceStream);
	//std::cout << "Bond streaming service has notified all listeners." << std::endl;
}


#endif // !BONDSTREAMINGSERVICE_HPP

