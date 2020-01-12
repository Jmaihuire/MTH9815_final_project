//
// Created by Zichao Wang on 2018/12/20.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALRISKSERVICE_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALRISKSERVICE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"
#include "MiddlePath/MiddlePathGeneral/riskservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartGeneral/historicaldataservice.hpp"
#include "HistoricalDataPart/HistoricalDataPartConnector/BondHistoricalRiskServiceConnector.hpp"


class BondHistoricalRiskService : public HistoricalDataService<PV01<Bond> >
{
private:
    // listener pointer list
    std::vector<ServiceListener<PV01<Bond> >*> listenerPtrs;
    // K : CUSIP; V : pv01 of this bond.
    std::map<std::string, PV01<Bond> > pv01s;

    BucketedSector<Bond>* frontEndPtr;
    BucketedSector<Bond>* bellyPtr;
    BucketedSector<Bond>* longEndPtr;

    BondHistoricalRiskServiceConnector* bondHistoricalRiskServiceConnectorPtr;

public:
    // ctor
    BondHistoricalRiskService(BondHistoricalRiskServiceConnector* _bondHistoricalRiskServiceConnectorPtr) : bondHistoricalRiskServiceConnectorPtr(_bondHistoricalRiskServiceConnectorPtr)
    {
        Bond TwoYBond("9128285Q9", CUSIP, "T", 0.15, boost::gregorian::date(2020, Dec, 8));
        Bond ThreeYBond("9128285L0", CUSIP, "T", 0.15, boost::gregorian::date(2021, Dec, 8));
        Bond FiveYBond("9128285P1", CUSIP, "T", 0.15, boost::gregorian::date(2023, Dec, 8));
        Bond SevenYBond("9128285N6", CUSIP, "T", 0.15, boost::gregorian::date(2025, Dec, 8));
        Bond TenYBond("9128285M8", CUSIP, "T", 0.15, boost::gregorian::date(2028, Dec, 8));
        Bond ThirtyYBond("912810SE9", CUSIP, "T", 0.15, boost::gregorian::date(2048, Dec, 8));

        std::vector<Bond> frontEndBonds = {TwoYBond, ThreeYBond};
        std::vector<Bond> bellyBonds = {FiveYBond, SevenYBond, TenYBond};
        std::vector<Bond> longEndBonds = {ThirtyYBond};
        frontEndPtr = new BucketedSector<Bond>(frontEndBonds, std::string("frontEnd"));
        bellyPtr = new BucketedSector<Bond>(bellyBonds, std::string("belly"));
        longEndPtr = new BucketedSector<Bond>(longEndBonds, std::string("longEnd"));
    }

    // Given CUSIP, get pv01 of this bond.
    PV01<Bond>& GetData(std::string CUSIP)
    {
        return pv01s.at(CUSIP);
    }

    std::map<std::string, PV01<Bond> >& GetPV01s()
    {
        return pv01s;
    }

    // Update pv01 and notify all listeners.
    // Create pv01 for this bond if it is a new CUSIP.
    void OnMessage(PV01<Bond>& pv01)
    {
        //std::cout << "BondHistoricalRiskService::OnMessage has: ";
        //pv01.Print();
        //std::cout << std::endl;

        std::string CUSIP = pv01.GetProduct().GetProductId();
        pv01s[CUSIP] = pv01;

        //std::cout << "pv01s[CUSIP]: ";
        //pv01s[CUSIP].Print();
        //std::cout << std::endl;

        for(auto& listenerPtr : listenerPtrs)
            listenerPtr->ProcessAdd(pv01);
    }

    // Add a listener pointer into pointer list.
    void AddListener(ServiceListener<PV01<Bond> >* listenerPtr)
    {
        listenerPtrs.push_back(listenerPtr);
    }

    // Get all listener pointers.
    const std::vector<ServiceListener<PV01<Bond> >*>& GetListeners() const
    {
        return listenerPtrs;
    }

    // Get pv01 for given bucket of securities.
    double GetBucketedRisk(BucketedSector<Bond>& bucketedSector)
    {

        double sectoredPV01 = 0;
        for (auto& bond : bucketedSector.GetProducts())
        {
            if (pv01s.find(bond.GetProductId()) != pv01s.end())
                sectoredPV01 += pv01s.at(bond.GetProductId()).GetPV01();
        }

        return sectoredPV01;
    }

    // Publish pv01 into risk.txt by invoking Connector::Publish().
    void PersistData(std::string cusip, PV01<Bond>& pv01)
    {
        // Get pv01 for this single bond.
        bondHistoricalRiskServiceConnectorPtr->PublishSingleRisk(pv01);

        // Get pv01s for three bucket sectors.
        bondHistoricalRiskServiceConnectorPtr->PublishBucketedRisk(GetBucketedRisk(*frontEndPtr), GetBucketedRisk(*bellyPtr), GetBucketedRisk(*longEndPtr));
    }

};


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALRISKSERVICE_HPP
