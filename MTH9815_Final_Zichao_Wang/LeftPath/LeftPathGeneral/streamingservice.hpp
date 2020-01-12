/**
 * streamingservice.hpp
 * Defines the data types and Service for price streams.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 7, 2018


#ifndef STREAMING_SERVICE_HPP
#define STREAMING_SERVICE_HPP

#include "../../Foundation/soa.hpp"
#include "../../Foundation/products.hpp"
#include "pricingservice.hpp"
#include "RightPath/RightPathGeneral/marketdataservice.hpp"


/**
 * A price stream order with price and quantity (visible and hidden)
 */
class PriceStreamOrder
{
private:
	double price;
	long visibleQuantity;
	long hiddenQuantity;
	PricingSide side;

public:
	// ctor for an order
	PriceStreamOrder() {}  // default ctor

	PriceStreamOrder(double _price, long _visibleQuantity, long _hiddenQuantity, PricingSide _side)
	{
		price = _price;
		visibleQuantity = _visibleQuantity;
		hiddenQuantity = _hiddenQuantity;
		side = _side;
	}

	// copy ctor
	PriceStreamOrder(const PriceStreamOrder& _priceStreamOrder)
	{
		price = _priceStreamOrder.GetPrice();
		visibleQuantity = _priceStreamOrder.GetVisibleQuantity();
		hiddenQuantity = _priceStreamOrder.GetHiddenQuantity();
		side = _priceStreamOrder.GetSide();
	}

	// assignment operator
	PriceStreamOrder& operator =(const PriceStreamOrder& _priceStreamOrder)
	{
		price = _priceStreamOrder.GetPrice();
		visibleQuantity = _priceStreamOrder.GetVisibleQuantity();
		hiddenQuantity = _priceStreamOrder.GetHiddenQuantity();
		side = _priceStreamOrder.GetSide();
		return *this;
	}

	// Get the side, price, visible and hidden quantity on this order.
	PricingSide GetSide() const
	{
		return side;
	}
	
	double GetPrice() const
	{
		return price;
	}
	
	long GetVisibleQuantity() const
	{
		return visibleQuantity;
	}
	
	long GetHiddenQuantity() const
	{
		return hiddenQuantity;
	}

	// Set the side, price, visible and hidden quantity on this order.
	void SetSide(PricingSide  _side)
	{
		side = _side;
	}

	void SetPrice(double _price)
	{
		price = _price;
	}

	void SetVisibleQuantity(long _visibleQuantity)
	{
		visibleQuantity = _visibleQuantity;
	}

	void SetHiddenQuantity(long _hiddenQuantity)
	{
		hiddenQuantity = _hiddenQuantity;
	}

	// Print price stream order info.
	void Print() const;
	
};

void PriceStreamOrder::Print() const
{
	cout << "Price: " << price << ", visible quantity: " << visibleQuantity << ", hidden quantity: " << hiddenQuantity << ", side: ";
	if (side == BID)
		cout << "bid";
	else
		cout << "offer";
}


/**
 * Price Stream with a two-way market.
 * Type T is the product type.
 */
template<typename T>
class PriceStream
{
private:
	T product;
	PriceStreamOrder bidOrder;
	PriceStreamOrder offerOrder;

public:
	// ctor
	PriceStream() {}  // default ctor

	PriceStream(const T &_product, const PriceStreamOrder &_bidOrder, const PriceStreamOrder &_offerOrder) : product(_product), bidOrder(_bidOrder), offerOrder(_offerOrder) {}

	// copy ctor
	PriceStream(const PriceStream& _priceStream)
	{
		product = _priceStream.GetProduct();
		bidOrder = _priceStream.GetBidOrder();
		offerOrder = _priceStream.GetOfferOrder();
	}

	// assignment operator
	PriceStream<T>& operator =(const PriceStream<T>& _priceStream)
	{
		product = _priceStream.GetProduct();
		bidOrder = _priceStream.GetBidOrder();
		offerOrder = _priceStream.GetOfferOrder();
		return *this;
	}

	// Get the product, bid and offer order.
	const T& GetProduct() const
	{
		return product;
	}
	
	const PriceStreamOrder& GetBidOrder() const
	{
		return bidOrder;
	}
	
	const PriceStreamOrder& GetOfferOrder() const
	{
		return offerOrder;
	}

	// Set the product, bid and offer order.
	void SetProduct(T _product)
	{
		product = _product;
	}

	void SetBidOrder(PriceStreamOrder _bidOrder)
	{
		bidOrder = _bidOrder;
	}

	void SetOfferOrder(PriceStream _offerOrder)
	{
		offerOrder = _offerOrder;
	}

	// Print price stream.
	void Print() const;

};


template<typename T>
void PriceStream<T>::Print() const
{
	cout << "CUSIP: " << product.GetProductId() << "; bid order: ";
	GetBidOrder().Print();
	cout << "; offer order: ";
	GetOfferOrder().Print();
}


/**
 * Streaming service to publish two-way prices.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class StreamingService : public Service<string, PriceStream<T> >
{
public:
	// Since we will publish data using historical data service,
	// we  will not use this PublishPrice().

	// Publish two-way prices
	//virtual void PublishPrice(PriceStream<T>& priceStream);

};


// algo stream class
class AlgoStream
{
private:
	// AlgoStream object bears a PriceStream object.
	PriceStream<Bond> priceStream;

public:
	// ctor and dtor
	// Use some existed algorithm to generate
	// price stream according to price.
	AlgoStream() = default;

	AlgoStream(const Price<Bond>& price)
	{
		Bond bond = price.GetProduct();
		double mid = price.GetMid();
		double spread = price.GetBidOfferSpread();
		double bid = mid + spread * 0.5;
		double offer = mid - spread * 0.5;

		// This is just a simplification of some trading algo.
		long bidVisibleQuantity = 1000000;
		long bidHiddenQuantity = 2000000;
		long offerVisibleQuantity = 2000000;
		long offerHiddenQuantity = 4000000;

		PriceStreamOrder bidStreamOrder(bid, bidVisibleQuantity, bidHiddenQuantity, BID);
		PriceStreamOrder offerStreamOrder(offer, offerVisibleQuantity, offerHiddenQuantity, OFFER);
		priceStream = PriceStream<Bond>(bond, bidStreamOrder, offerStreamOrder);
	}

	// copy ctor
	AlgoStream(const AlgoStream & _algoStream)
	{
		priceStream = _algoStream.GetPriceStream();
	}
	
	~AlgoStream() {}  // dtor

	// assignment operator
	AlgoStream& operator =(const AlgoStream& _algoStream)
	{
		priceStream = _algoStream.GetPriceStream();
		return *this;
	}

	// Get and set price stream pointer.
	PriceStream<Bond> GetPriceStream() const
	{
		return priceStream;
	}

	void SetPriceStream(PriceStream<Bond>& _priceStream)
	{
		priceStream = _priceStream;
	}

	// Update its internal price stream object when new price comes.
	void UpdatePriceStream(const Price<Bond>& price);

	// Print streaming service.
	void Print()
	{
		priceStream.Print();
	}
};

void AlgoStream::UpdatePriceStream(const Price<Bond>& price)
{
	// First check if new and old prices refer to the same bond.
	if (price.GetProduct().GetProductId() != priceStream.GetProduct().GetProductId())
		return;

	// If they refer to the same bond, we substitute the old internal
	// price stream object with the new one.
	double mid = price.GetMid();
	double spread = price.GetBidOfferSpread();
	double bid = mid + spread * 0.5;
	double offer = mid - spread * 0.5;

	// This is just a simplification of some trading algo.
	long bidVisibleQuantity = 1000000;
	long bidHiddenQuantity = 2000000;
	long offerVisibleQuantity = 2000000;
	long offerHiddenQuantity = 4000000;

	PriceStreamOrder bidStreamOrder(bid, bidVisibleQuantity, bidHiddenQuantity, BID);
	PriceStreamOrder offerStreamOrder(offer, offerVisibleQuantity, offerHiddenQuantity, OFFER);
	PriceStream<Bond> newPriceStream(price.GetProduct(), bidStreamOrder, offerStreamOrder);

	priceStream = newPriceStream;

}


#endif
