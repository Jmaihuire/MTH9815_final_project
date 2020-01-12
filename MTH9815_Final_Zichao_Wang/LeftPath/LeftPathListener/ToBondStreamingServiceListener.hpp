// ToBondStreamingServiceListener.hpp
// Created by Zichao Wang
// Date: Dec 9, 2018

// data flow:
// BondAlgoStreamingService --> ToBondStreamingServiceListener --> BondStreaing Service

#ifndef TOBONDSTREAMINGSERVICELISTENER_HPP
#define TOBONDSTREAMINGSERVICELISTENER_HPP

#include "../../Foundation/soa.hpp"
#include "../../Foundation/products.hpp"
#include "../LeftPathGeneral/streamingservice.hpp"
#include "../LeftPathService/BondStreamingService.hpp"


class ToBondStreamingServiceListener : public ServiceListener<AlgoStream>
{
private:
	BondStreamingService * bondStreamingServicePtr;

public:
	// ctor
	ToBondStreamingServiceListener(BondStreamingService * _bondStreamingServicePtr) : bondStreamingServicePtr(_bondStreamingServicePtr) {}

	void ProcessAdd(AlgoStream& algoStream)
	{
		//std::cout << "to bond streaming service connector receives: ";
		//algoStream.Print();
		//std::cout << std::endl;
		// Add new price stream into hash table in bond streaming service.
		bondStreamingServicePtr->AddPriceStream(algoStream);

		// Make bond streaming service publish price stream into txt file.
		//PriceStream<Bond> priceStream = algoStream.GetPriceStream();
		//bondStreamingServicePtr->PublishPrice(priceStream);
	}

	void ProcessRemove(AlgoStream& data) {}  // no impelmentation
	void ProcessUpdate(AlgoStream& data) {}  // no impelmentation
};


#endif // !TOBONDSTREAMINGSERVICELISTENER_HPP


