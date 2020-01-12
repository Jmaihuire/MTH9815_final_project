/**
 * tradebookingservice.hpp
 * Defines the data types and Service for trade booking.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 9, 2018


#ifndef TRADE_BOOKING_SERVICE_HPP
#define TRADE_BOOKING_SERVICE_HPP

#include <string>
#include <vector>

#include "Foundation/soa.hpp"
#include "Foundation/products.hpp"


// Trade sides
enum Side { BUY, SELL };

/**
 * Trade object with a price, side, and quantity on a particular book.
 * Type T is the product type.
 */
template<typename T>
class Trade
{
private:
	T product;
	string tradeId;
	double price;
	string book;
	long quantity;
	Side side;

public:
	// ctor for a trade
	Trade() = default;

	Trade(const T &_product, string _tradeId, double _price, string _book, long _quantity, Side _side) : product(_product)
	{
		tradeId = _tradeId;
		price = _price;
		book = _book;
		quantity = _quantity;
		side = _side;
	}

	// Get the product
	const T& GetProduct() const
	{
		return product;
	}

	// Get the trade ID
	const string& GetTradeId() const
	{
		return tradeId;
	}

	// Get the mid price
	double GetPrice() const
	{
		return price;
	}

	// Get the book
	const string& GetBook() const
	{
		return book;
	}

	// Get the quantity
	long GetQuantity() const
	{
		return quantity;
	}

	// Get the side
	Side GetSide() const
	{
		return side;
	}

	// Print trade info.
	void Print();

};

template<typename T>
void Trade<T>::Print()
{
	std::cout << "Trade id: " << tradeId
		<< ", CUSIP: " << product.GetProductId()
		<< ", book: " << book
		<< ", price: " << price
		<< ", quantity: " << quantity
		<< ", side: " << (side == BUY ? "BUY" : "SELL");
}


/**
 * Trade Booking Service to book trades to a particular book.
 * Keyed on trade id.
 * Type T is the product type.
 */
template<typename T>
class TradeBookingService : public Service<string,Trade <T> >
{
public:
	// Book the trade
	virtual void BookTrade(Trade<T>& trade) = 0;

};

#endif
