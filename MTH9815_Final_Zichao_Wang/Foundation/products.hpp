/**
 * products.hpp
 * Defines Bond and Interest Rate Swap products.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 7, 2018


#ifndef PRODUCTS_HPP
#define PRODUCTS_HPP

#include <iostream>
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;


enum ProductType { IRSWAP, BOND };

/**
 * Base class for a product.
 */
class Product
{
private:
	string productId;
	ProductType productType;

public:
	// ctor for a prduct
	Product() : productId(""), productType(BOND) {}

	Product(string _productId, ProductType _productType)
	{
		productId = _productId;
		productType = _productType;
	}

	// copy ctor
	Product(const Product& _product)
	{
		productId = _product.GetProductId();
		productType = _product.GetProductType();
	}

	// assignment operator
	Product& operator =(const Product& _product)
	{
		productId = _product.GetProductId();
		productType = _product.GetProductType();
		return *this;
	}

	// Get the product identifier and product type.
	const string& GetProductId() const
	{
		return productId;
	}
	
	const ProductType GetProductType() const
	{
		return productType;
	}

	// Set the product identifier and product type.
	void SetProductId(string _productId)
	{
		productId = _productId;
	}

	void SetProductType(ProductType _productType)
	{
		productType = _productType;
	}

};


enum BondIdType { CUSIP, ISIN };

/**
 * Bond product class
 */
class Bond : public Product
{
private:
	string productId;
	BondIdType bondIdType;
	string ticker;
	float coupon;
	date maturityDate;

public:
	// ctor for a bond
	Bond() : Product("", BOND) {}

	Bond(string _productId, BondIdType _bondIdType, string _ticker, float _coupon, date _maturityDate) : Product(_productId, BOND)
	{
		productId = _productId;
		bondIdType = _bondIdType;
		ticker = _ticker;
		coupon = _coupon;
		maturityDate = _maturityDate;
	}

	// copy ctor
	Bond(const Bond& _bond)
	{
		productId = _bond.GetProductId();
		bondIdType = _bond.GetBondIdType();
		ticker = _bond.GetTicker();
		coupon = _bond.GetCoupon();
		maturityDate = _bond.GetMaturityDate();
	}

	// assignment operator
	Bond& operator =(const Bond& _bond)
	{
		productId = _bond.GetProductId();
		bondIdType = _bond.GetBondIdType();
		ticker = _bond.GetTicker();
		coupon = _bond.GetCoupon();
		maturityDate = _bond.GetMaturityDate();
		return *this;
	}

	// Get the ticker, coupon, maturity date, id type, product id.
	const string& GetTicker() const
	{
		return ticker;
	}
	
	float GetCoupon() const
	{
		return coupon;
	}
	
	const date& GetMaturityDate() const
	{
		return maturityDate;
	}
	
	const BondIdType GetBondIdType() const
	{
		return bondIdType;
	}

	const string& GetProductId() const
	{
		return productId;
	}

	// Set the ticker, coupon, maturity date, id type, product id.
	void SetTicker(string _ticker)
	{
		ticker = _ticker;
	}

	void SetCoupon(float _coupon)
	{
		coupon = _coupon;
	}

	void SetMaturityDate(date _maturityDate)
	{
		maturityDate = _maturityDate;
	}

	void SetBondIdType(BondIdType _bondIdType)
	{
		bondIdType = _bondIdType;
	}
	
	// Print the bond
	void Print() const
	{
		cout << "CUSIP: " << productId << ", ticker: " << ticker << ", coupon: " << coupon << ", maturity date: " << maturityDate;
	}

};


#endif
