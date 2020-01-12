// ToBondAlgoStreamingServiceListener.hpp
// Created by Zichao Wang
// Date: Dec 8, 2018

// data flow:
// BondPricingService --> ToBondAlgoStreamingServiceListener --> BondAlgoStreamingService

#ifndef TOBONDALGOSTREAMINGSERVICELISTENER_HPP
#define TOBONDALGOSTREAMINGSERVICELISTENER_HPP

#include "../../Foundation/soa.hpp"
#include "../LeftPathGeneral/streamingservice.hpp"
#include "../LeftPathService/BondPricingService.hpp"
#include "../LeftPathService/BondAlgoStreamingService.hpp"


class ToBondAlgoStreamingServiceListener : public ServiceListener<Price<Bond> >
{
private:
	// service it wants to pass data to
	BondAlgoStreamingService * bondAlgoStreamingServicePtr;

public:
	// ctor
	ToBondAlgoStreamingServiceListener(BondAlgoStreamingService* _bondAlgoStreamingServicePtr) : bondAlgoStreamingServicePtr(_bondAlgoStreamingServicePtr) {}

	// We will only implement ProcessAdd() function.
	void ProcessAdd(Price<Bond> & price)
	{
		// New data flows into bond algo streaming service.
		//std::cout << "to bond algo listener receives: ";
		//price.Print();
		//std::cout << std::endl;
		bondAlgoStreamingServicePtr->AddAlgoStream(price);
	}

	void ProcessRemove(Price<Bond> & data) {}
	void ProcessUpdate(Price<Bond> & data) {}

};


#endif // !TOBONDALGOSTREAMINGSERVICELISTENER_HPP
