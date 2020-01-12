//
// Created by Zichao Wang on 2018/12/14.
//

#ifndef MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALPOSITIONCONNECTOR_HPP
#define MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALPOSITIONCONNECTOR_HPP

#include <iostream>
#include <fstream>

#include "Foundation/soa.hpp"
#include "MiddlePath/MiddlePathGeneral/positionservice.hpp"

// data flow:
// BondHistoricalPositionService --> BondHistoricalPositionServiceConnector --> positions.txt


class BondHistoricalPositionServiceConnector : public Connector<Position<Bond> >
{
public:
    // ctor
    BondHistoricalPositionServiceConnector() = default;

    // Write a position into positions.txt.
    void Publish(Position<Bond>& position);

    void Subscribe() {}  // No implementation.
};

void BondHistoricalPositionServiceConnector::Publish(Position<Bond> &position)
{
    std::ofstream f;
    f.open("C:\\Users\\Zichao Wang\\Desktop\\Baruch\\Fall Semester\\Software Engineering\\MTH9815_Final_Zichao_Wang\\positions.txt", ios::app);

    // If open successfully
    if (f.is_open())
    {
        // First print CUSIP identifier.
        f << "CUSIP: " << position.GetProduct().GetProductId() << "; ";

        // Then print position of each book as well as aggregate position.
        for (auto& pair : position.GetPositions())
            f << "book: " << pair.first << ", position: " << pair.second << "; ";
            //aggregatePosition += pair.second;
        f << "aggregate position: " << position.GetAggregatePosition() << ".";

        f << std::endl;
    }
    else
    {
        std::cout << "Cannot open or create position.txt." << std::endl;
        exit(-1);
    }
    f.close();
}


#endif //MTH9815_FINAL_ZICHAO_WANG_BONDHISTORICALPOSITIONCONNECTOR_HPP
