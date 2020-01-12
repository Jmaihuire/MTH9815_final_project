/**
 * historicaldataservice.hpp
 * historicaldataservice.hpp
 *
 * @author Breman Thuraisingham
 * Defines the data types and Service for historical data.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 13, 2018

#ifndef HISTORICAL_DATA_SERVICE_HPP
#define HISTORICAL_DATA_SERVICE_HPP

#include <iostream>
#include <string>
#include <fstream>

#include "Foundation/soa.hpp"


/**
 * Service for processing and persisting historical data to a persistent store.
 * Keyed on some persistent key.
 * Type T is the data type to persist.
 */
template<typename T>
class HistoricalDataService : Service<string,T>
{
public:
    // Persist data to a store
    virtual void PersistData(string persistKey, T& data) = 0;

};

#endif
