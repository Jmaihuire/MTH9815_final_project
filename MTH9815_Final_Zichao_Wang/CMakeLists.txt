cmake_minimum_required(VERSION 3.13)
project(MTH9815_Final_Zichao_Wang)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Foundation)
include_directories(LeftPath)
include_directories(LeftPath/LeftPathConnector)
include_directories(LeftPath/LeftPathGeneral)
include_directories(LeftPath/LeftPathListener)
include_directories(LeftPath/LeftPathService)

include_directories(C:\\local\\boost_1_66_0)
link_directories(C:\\local\\boost_1_66_0\\lib32-msvc-14.1)

add_executable(MTH9815_Final_Zichao_Wang
        Foundation/products.hpp
        Foundation/soa.hpp
        LeftPath/LeftPathConnector/BondPricingServiceConnector.hpp
        LeftPath/LeftPathGeneral/pricingservice.hpp
        LeftPath/LeftPathGeneral/streamingservice.hpp
        LeftPath/LeftPathListener/ToBondAlgoStreamingServiceListener.hpp
        LeftPath/LeftPathListener/ToBondStreamingServiceListener.hpp
        LeftPath/LeftPathService/BondAlgoStreamingService.hpp
        LeftPath/LeftPathService/BondPricingService.hpp
        LeftPath/LeftPathService/BondStreamingService.hpp
        BondInfoHelper.hpp
        MiddlePath/MiddlePathService/BondPositionService.hpp
        MiddlePath/MiddlePathService/BondRiskService.hpp
        MiddlePath/MiddlePathService/BondTradeBookingService.hpp
        MiddlePath/MiddlePathConnector/BondTradeBookingServiceConnector.hpp
        RightPath/RightPathGeneral/executionservice.hpp
        HistoricalDataPart/HistoricalDataPartGeneral/historicaldataservice.hpp
        InquiryPart/InquiryPartGeneral/inquiryservice.hpp
        RightPath/RightPathGeneral/marketdataservice.hpp
        MiddlePath/MiddlePathGeneral/positionservice.hpp
        MiddlePath/MiddlePathGeneral/riskservice.hpp
        Source.cpp
        MiddlePath/MiddlePathListener/ToBondPositionServiceListener.hpp
        MiddlePath/MiddlePathListener/ToBondRiskServiceListener.hpp
        MiddlePath/MiddlePathGeneral/tradebookingservice.hpp HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalPositionServiceConnector.hpp HistoricalDataPart/HistoricalDataPartService/BondHistoricalPositionService.hpp HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalPositionServiceListener.hpp HistoricalDataPart/HistoricalDataPartService/BondHistoricalStreamingService.hpp HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalStreamingServiceListener.hpp HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalStreamingServiceConnector.hpp HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalRiskServiceListener.hpp HistoricalDataPart/HistoricalDataPartService/BondHistoricalRiskService.hpp HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalRiskServiceConnector.hpp RightPath/RightPathService/BondMarketDataService.hpp RightPath/RightPathConnector/BondMarketDataServiceConnector.hpp RightPath/RightPathService/BondAlgoExecutionService.hpp RightPath/RightPathListener/ToBondAlgoExecutionServiceListener.hpp RightPath/RightPathService/BondExecutionService.hpp RightPath/RightPathListener/ToBondExecutionServiceListener.hpp HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalExecutionServiceListener.hpp HistoricalDataPart/HistoricalDataPartService/BondHistoricalExecutionService.hpp HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalExecutionServiceConnector.hpp InquiryPart/InquiryPartService/BondInquiryService.hpp InquiryPart/InquiryPartConnector/BondInquiryServiceConnector.hpp HistoricalDataPart/HistoricalDataPartService/BondHistoricalInquiryService.hpp HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalInquiryServiceConnector.hpp HistoricalDataPart/HistoricalDataPartListener/ToBondHistoricalInquiryServiceListener.hpp GUIPart/ToBondGUIServiceListener.hpp GUIPart/BondGUIService.hpp GUIPart/BondGUIServiceConnector.hpp)
