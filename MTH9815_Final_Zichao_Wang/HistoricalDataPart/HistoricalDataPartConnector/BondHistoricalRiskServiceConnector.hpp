//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALRISKSERVICECONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALRISKSERVICECONNECTOR_HPP


#include <iostream>
#include <fstream>

#include "Foundation/soa.hpp"
#include "MiddlePath/MiddlePathGeneral/riskservice.hpp"

// data flow:
// BondHistoricalRiskService --> BondHistoricalRiskServiceConnector --> risk.txt


class BondHistoricalRiskServiceConnector : public Connector<PV01<Bond> >
{
public:
    // ctor
    BondHistoricalRiskServiceConnector() = default;

    // Write risk into risk.txt.
    void Publish(PV01<Bond>& pv01) {};
    void PublishSingleRisk(PV01<Bond>& pv01);
    void PublishBucketedRisk(double frontEndPV01, double bellyPV01, double longEndPV01);

    void Subscribe() {}  // No implementation.
};

void BondHistoricalRiskServiceConnector::PublishSingleRisk(PV01<Bond> &pv01)
{
    std::ofstream f;
    f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\risk.txt", ios::app);

    // If open successfully
    if (f.is_open())
    {
        // First print CUSIP identifier.
        f << "CUSIP: " << pv01.GetProduct().GetProductId() << ", pv01: " << pv01.GetPV01() << "; ";
    }
    else
    {
        std::cout << "Cannot open or create position.txt." << std::endl;
        exit(-1);
    }
    f.close();
}

void BondHistoricalRiskServiceConnector::PublishBucketedRisk(double frontEndPV01, double bellyPV01, double longEndPV01)
{
    std::ofstream f;
    f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\risk.txt", ios::app);

    // If open successfully
    if (f.is_open())
    {
        // First print CUSIP identifier.
        f << "front end PV01: " << frontEndPV01 << ", belly PV01: " << bellyPV01 << ", long end PV01: " << longEndPV01 << std::endl;
    }
    else
    {
        std::cout << "Cannot open or create position.txt." << std::endl;
        exit(-1);
    }
    f.close();
}


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALRISKSERVICECONNECTOR_HPP
