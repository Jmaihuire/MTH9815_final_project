/**
 * riskservice.hpp
 * Defines the data types and Service for fixed income risk.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 10, 2018


#ifndef RISK_SERVICE_HPP
#define RISK_SERVICE_HPP

#include "Foundation/soa.hpp"
#include "positionservice.hpp"

#include <string>
#include <map>
#include <iostream>
#include <utility>


class CurrentPV01Table
{
private:
	std::map<std::string, double> currentPV01Table;

public:
	// Theoretically, we can get current pv01 on "https://fixedincome.fidelity.com/ftgw/fi/filanding".
	// But since it is not a free service, I just assign some pv01 values myself linearly.
	CurrentPV01Table()
	{
		currentPV01Table.insert(std::pair<std::string, double>("9128285Q9", 0.02));
		currentPV01Table.insert(std::pair<std::string, double>("9128285L0", 0.03));
		currentPV01Table.insert(std::pair<std::string, double>("9128285P1", 0.05));
		currentPV01Table.insert(std::pair<std::string, double>("9128285N6", 0.07));
		currentPV01Table.insert(std::pair<std::string, double>("9128285M8", 0.1));
		currentPV01Table.insert(std::pair<std::string, double>("912810SE9", 0.3));
	}

	// Get current pv01 value from a given CUSIP.
	double GetPV01(std::string CUSIP) const
	{
		return currentPV01Table.at(CUSIP);
	}

};

CurrentPV01Table pv01Table;


/**
 * PV01 risk.
 * Type T is the product type.
 */
template<typename T>
class PV01
{
private:
	T product;
	double pv01;
	long quantity;

public:
	// ctor for a PV01 value
	PV01() = default;

	PV01(const T &_product, double _pv01, long _quantity) : product(_product), pv01(_pv01), quantity(_quantity) {}

	// If just given a certain bond, we use current pv01 in pv01Table.
	PV01(const T & _product) : product(_product), quantity(0)
	{
		pv01 = pv01Table.GetPV01(_product.GetProductId());
	}

	// Get the product on this PV01 value
	const T& GetProduct() const
	{
		return product;
	}

	// Get the PV01 value
	double GetPV01() const
	{
		// Return pv01 * quantity will simplify our calculation in the following.
		return pv01 * quantity;
	}

	// Get the quantity that this risk value is associated with
	long GetQuantity() const
	{
		return quantity;
	}

	// Add a position into PV01.
	void AddQuantity(long quantityIncrement)
	{
		quantity += quantityIncrement;
	}

	void Print()
	{
		product.Print();
		std::cout << "; pv01: " << pv01 << "; quantity: " << quantity;
	}

};


/**
 * A bucket sector to bucket a group of securities.
 * We can then aggregate bucketed risk to this bucket.
 * Type T is the product type.
 */
template<typename T>
class BucketedSector
{
private:
	vector<T> products;  // various kinds of bonds
	string name;  // name of this bucket sector

public:
	// ctor for a bucket sector
	BucketedSector(const vector<T> &_products, string _name) : products(_products), name(_name) {}

	// Get the products associated with this bucket
	const vector<T>& GetProducts() const
	{
		return products;
	}

	// Get the name of the bucket
	const string& GetName() const
	{
		return name;
	}

};

/**
 * Risk Service to vend out risk for a particular security and across a risk bucketed sector.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class RiskService : public Service<string, PV01<T> >
{
public:
	// Add a position that the service will risk
	virtual void UpdatePosition(Position<T> &position) = 0;

	// Get the bucketed risk for the bucket sector
	//virtual double GetBucketedRisk(const BucketedSector<T> &sector) const = 0;

};


#endif
