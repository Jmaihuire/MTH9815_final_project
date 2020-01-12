
#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "BondInfoHelper.hpp"

// left path
#include "LeftPath/LeftPathGeneral/pricingservice.hpp"
#include "LeftPath/LeftPathGeneral/streamingservice.hpp"

#include "LeftPath/LeftPathService/BondPricingService.hpp"
#include "LeftPath/LeftPathService/BondAlgoStreamingService.hpp"
#include "LeftPath/LeftPathService/BondStreamingService.hpp"

#include "LeftPath/LeftPathConnector/BondPricingServiceConnector.hpp"

#include "LeftPath/LeftPathListener/ToBondAlgoStreamingServiceListener.hpp"
#include "LeftPath/LeftPathListener/ToBondStreamingServiceListener.hpp"

#include "HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalStreamingServiceListener.hpp"
#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalStreamingService.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalStreamingServiceConnector.hpp"


// middle path
#include "MiddlePath/MiddlePathGeneral/tradebookingservice.hpp"
#include "MiddlePath/MiddlePathGeneral/positionservice.hpp"

#include "MiddlePath/MiddlePathService/BondTradeBookingService.hpp"
#include "MiddlePath/MiddlePathService/BondPositionService.hpp"
#include "MiddlePath/MiddlePathService/BondRiskService.hpp"

#include "MiddlePath/MiddlePathConnector/BondTradeBookingServiceConnector.hpp"

#include "MiddlePath/MiddlePathListener/ToBondPositionServiceListener.hpp"
#include "MiddlePath/MiddlePathListener/ToBondRiskServiceListener.hpp"

#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalPositionService.hpp"
#include "HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalPositionServiceListener.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalPositionServiceConnector.hpp"

#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalRiskService.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalRiskServiceConnector.hpp"
#include "HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalRiskServiceListener.hpp"


// right path
#include "RightPath/RightPathConnector/BondMarketDataServiceConnector.hpp"

#include "RightPath/RightPathListener/ToBondAlgoExecutionServiceListener.hpp"
#include "RightPath/RightPathListener/ToBondExecutionServiceListener.hpp"

#include "RightPath/RightPathService/BondAlgoExecutionService.hpp"
#include "RightPath/RightPathService/BondMarketDataService.hpp"
#include "RightPath/RightPathService/BondExecutionService.hpp"

#include "HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalExecutionServiceListener.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalExecutionServiceConnector.hpp"
#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalExecutionService.hpp"


// inquiry part
#include "InquiryPart/InquiryPartService/BondInquiryService.hpp"
#include "InquiryPart/InquiryPartConnector/BondInquiryServiceConnector.hpp"

#include "HistoricalDataPart/HistoricalDataPartService/BondHistoricalInquiryService.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalInquiryServiceConnector.hpp"
#include "HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalInquiryServiceListener.hpp"


// GUI part
#include "GUIPart/BondGUIService.hpp"
#include "GUIPart/BondGUIServiceConnector.hpp"
#include "GUIPart/ToBondGUIServiceListener.hpp"


#include <iostream>


int main()
{
	// test for "BondHelperInfo.hpp"
	/*
	std::cout << CUSIPToIndex("9128285N6") << std::endl;
	std::cout << CalculatePrice("100-254") << std::endl;
	std::cout << CalculatePrice("99-254") << std::endl;
	*/

	// test for "BondPricingService.hpp"
	/*
	BondPricingService bondPricingService;
	BondPricingServiceConnector bondPricingConnector("connector", bondPricingService);

	bondPricingService.Print();
	std::cout << std::endl;
	*/


	// test for left path
	// Create first three services.
	BondPricingService * bondPricingServicePtr = new BondPricingService();
	BondAlgoStreamingService * bondAlgoStreamingServicePtr = new BondAlgoStreamingService();
	BondStreamingService * bondStreamingServicePtr = new BondStreamingService();

	// Create first two listeners.
	ToBondAlgoStreamingServiceListener * toBondAlgoStreamingServiceListenerPtr = new ToBondAlgoStreamingServiceListener(bondAlgoStreamingServicePtr);

	ToBondStreamingServiceListener * toBondStreamingServiceListenerPtr = new ToBondStreamingServiceListener(bondStreamingServicePtr);

	// Add first two listeners.
	bondPricingServicePtr->AddListener(toBondAlgoStreamingServiceListenerPtr);
	bondAlgoStreamingServicePtr->AddListener((toBondStreamingServiceListenerPtr));

	// Create two connectors.
	BondPricingServiceConnector* bondPricingServiceConnectorPtr = new BondPricingServiceConnector(bondPricingServicePtr);
	BondHistoricalStreamingServiceConnector * bondHistoricalStreamingServiceConnectorPtr = new BondHistoricalStreamingServiceConnector();

	// Create publish-only service.
	BondHistoricalStreamingService * bondHistoricalStreamingServicePtr = new BondHistoricalStreamingService(bondHistoricalStreamingServiceConnectorPtr);

	// Create last listener.
	ToBondHistoricalStreamingServiceListener * toBondHistoricalStreamingServiceListenerPtr = new ToBondHistoricalStreamingServiceListener(bondHistoricalStreamingServicePtr);

	// Add second listener.
	bondStreamingServicePtr->AddListener(toBondHistoricalStreamingServiceListenerPtr);

	// GUI part.
	BondGUIServiceConnector* bondGUIServiceConnectorPtr = new BondGUIServiceConnector();
	BondGUIService* bondGUiServicePtr = new BondGUIService(bondGUIServiceConnectorPtr);
	ToBondGUIServiceListener* toBondGUIServiceListenerPtr = new ToBondGUIServiceListener(bondGUiServicePtr);

    bondPricingServicePtr->AddListener(toBondGUIServiceListenerPtr);

	// Subscribe from "prices.txt".
	bondPricingServiceConnectorPtr->Subscribe("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\prices.txt");





	// test for middle path.
	// Create first three services.
	BondTradeBookingService * bondTradeBookingServicePtr = new BondTradeBookingService();
	BondPositionService * bondPositionServicePtr = new BondPositionService();
	BondRiskService * bondRiskServicePtr = new BondRiskService();

	// Create first two listeners.
	ToBondPositionServiceListener * toBondPositionServiceListenerPtr = new ToBondPositionServiceListener(bondPositionServicePtr);
	ToBondRiskServiceListener * toBondRiskServiceListenerPtr = new ToBondRiskServiceListener(bondRiskServicePtr);

	// Add first two listeners.
	bondTradeBookingServicePtr->AddListener(toBondPositionServiceListenerPtr);
	bondPositionServicePtr->AddListener(toBondRiskServiceListenerPtr);

	// Create first connector.
	BondTradeBookingServiceConnector * bondTradeBookingServiceConnectorPtr = new BondTradeBookingServiceConnector(bondTradeBookingServicePtr);

	// Create BondHistoricalPosition part.
	BondHistoricalPositionServiceConnector * bondHistoricalPositionServiceConnectorPtr = new BondHistoricalPositionServiceConnector();
	BondHistoricalPositionService* bondHistoricalPositionServicePtr = new BondHistoricalPositionService(bondHistoricalPositionServiceConnectorPtr);
	ToBondHistoricalPositionServiceListener * toBondHistoricalPositionServiceListenerPtr = new ToBondHistoricalPositionServiceListener(bondHistoricalPositionServicePtr);

	// Add ToBondHistoricalPositionServiceListener.
	bondPositionServicePtr->AddListener(toBondHistoricalPositionServiceListenerPtr);

	// Create BondHistoricalRisk part.
	BondHistoricalRiskServiceConnector * bondHistoricalRiskServiceConnectorPtr = new BondHistoricalRiskServiceConnector();
	BondHistoricalRiskService* bondHistoricalRiskServicePtr = new BondHistoricalRiskService(bondHistoricalRiskServiceConnectorPtr);
	ToBondHistoricalRiskServiceListener * toBondHistoricalRiskServiceListenerPtr = new ToBondHistoricalRiskServiceListener(bondHistoricalRiskServicePtr);

	// Add ToBondHistoricalRiskServiceListener.
	bondRiskServicePtr->AddListener(toBondHistoricalRiskServiceListenerPtr);


	// Subscribe from "trades.txt".
	bondTradeBookingServiceConnectorPtr->Subscribe("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\trades.txt");



    // test for right path
    // Create first three services.
    BondMarketDataService* bondMarketDataServicePtr = new BondMarketDataService();
    BondAlgoExecutionService* bondAlgoExecutionServicePtr = new BondAlgoExecutionService();
    BondExecutionService* bondExecutionServicePtr = new BondExecutionService();

    // Create first connector.
    BondMarketDataServiceConnector * bondMarketDataServiceConnectorPtr = new BondMarketDataServiceConnector(bondMarketDataServicePtr);

    // Create first two listeners.
    ToBondAlgoExecutionServiceListener* toBondAlgoExecutionServiceListenerPtr = new ToBondAlgoExecutionServiceListener(bondAlgoExecutionServicePtr);
    ToBondExecutionServiceListener* tobondExecutionServiceListenerPtr = new ToBondExecutionServiceListener(bondExecutionServicePtr);

    // Add first two listeners.
    bondMarketDataServicePtr->AddListener(toBondAlgoExecutionServiceListenerPtr);
    bondAlgoExecutionServicePtr->AddListener(tobondExecutionServiceListenerPtr);

    // Create historical data part.
    BondHistoricalExecutionServiceConnector* bondHistoricalExecutionServiceConnectorPtr = new BondHistoricalExecutionServiceConnector();
    BondHistoricalExecutionService* bondHistoricalExecutionServicePtr = new BondHistoricalExecutionService(bondHistoricalExecutionServiceConnectorPtr);
    ToBondHistoricalExecutionServiceListener* toBondHistoricalExecutionServiceListenerPtr = new ToBondHistoricalExecutionServiceListener(bondHistoricalExecutionServicePtr);
    bondExecutionServicePtr->AddListener(toBondHistoricalExecutionServiceListenerPtr);

    bondMarketDataServiceConnectorPtr->Subscribe("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\marketdata.txt");



    // test fot inquiry part
    BondInquiryService* bondInquiryServicePtr = new BondInquiryService();
    BondInquiryServiceConnector* bondInquiryServiceConnectorPtr = new BondInquiryServiceConnector(bondInquiryServicePtr);

    BondHistoricalInquiryServiceConnector* bondHistoricalInquiryServiceConnectorPtr = new BondHistoricalInquiryServiceConnector();
    BondHistoricalInquiryService* bondHistoricalInquiryServicePtr = new BondHistoricalInquiryService(bondHistoricalInquiryServiceConnectorPtr);
    ToBondHistoricalInquiryServiceListener* toBondHistoricalInquiryServiceListener = new ToBondHistoricalInquiryServiceListener(bondHistoricalInquiryServicePtr);

    bondInquiryServicePtr->AddListener(toBondHistoricalInquiryServiceListener);

    bondInquiryServiceConnectorPtr->Subscribe("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\inquiries.txt");


    return 0;
}