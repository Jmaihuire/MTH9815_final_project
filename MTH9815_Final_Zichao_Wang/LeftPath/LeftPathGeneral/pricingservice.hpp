/**
 * pricingservice.hpp
 * Defines the data types and Service for internal prices.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 7, 2018


#ifndef PRICING_SERVICE_HPP
#define PRICING_SERVICE_HPP

#include <string>
#include "../../Foundation/soa.hpp"
#include "../../Foundation/products.hpp"


/**
 * A price object consisting of mid and bid/offer spread.
 * Type T is the product type.
 */
template<typename T>
class Price
{

private:
	T product;
	double mid;
	double bidOfferSpread;

public:
	// ctor for a price
	Price() {}
	Price(const T& _product, double _mid, double _bidOfferSpread) : product(_product)
	{
		mid = _mid;
		bidOfferSpread = _bidOfferSpread;
	}

	// copy ctor.
	Price(const Price<T>& _price) : product(_price.GetProduct()), mid(_price.GetMid()), bidOfferSpread(_price.GetBidOfferSpread()) {}

	// assignment operator
	Price& operator =(const Price<T>& _price)
	{
		product = _price.GetProduct();
		mid = _price.GetMid();
		bidOfferSpread = _price.GetBidOfferSpread();
		return *this;
	}

	// Get the product, mid price, bid/offer spread around the mid.
	const T& GetProduct() const
	{
		return product;
	}
	
	double GetMid() const
	{
		return mid;
	}
	
	double GetBidOfferSpread() const
	{
		return bidOfferSpread;
	}

	// Set mid price and bid/offer spread.
	void SetMid(double _mid)
	{
		mid = _mid;
	}

	void SetSpread(double _bidOfferSpread)
	{
		bidOfferSpread = _bidOfferSpread;
	}

	// Print the price.
	void Print() const
	{
		cout << "CUSIP: " << product.GetProductId() << ", mid: " << mid << ", spread: " << bidOfferSpread;
	}

};

/**
 * Pricing Service managing mid prices and bid/offers.
 * Keyed on product identifier.
 * Type T is the product type.
 */
// We do not need PricingService class because we'll derive
// BondPricingService class directly from Service.
/*
template<typename T>
class PricingService : public Service<string,Price <T> >
{
};
*/


#endif
