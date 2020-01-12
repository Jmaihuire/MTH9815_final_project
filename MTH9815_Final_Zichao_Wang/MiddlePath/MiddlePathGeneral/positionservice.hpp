/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 10, 2018

#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include <iostream>

#include "Foundation/soa.hpp"
#include "tradebookingservice.hpp"

using namespace std;


/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{
private:
	T product;
	map<string, long> positions;  // K : book; V : position

public:
	// ctor for a position
	Position() = default;

	Position(const T &_product) : product(_product) {}

	// Get the product
	const T& GetProduct() const
	{
		return product;
	}

	// Get the position quantity of a certain book.
	long GetPosition(string &book)
	{
		return positions[book];
	}

	// Get the aggregate position of all books.
	long GetAggregatePosition()
	{
		long aggregatePosition = 0;
		for (auto& pair : positions)
			aggregatePosition += pair.second;
		return aggregatePosition;
	}

	void AddPosition(const string& book, long quantity)
	{
		// If this book does not exist before, create this book 
		// in hash table and add this quantity.
		if (positions.find(book) != positions.end())
			positions[book] += quantity;
		else
			positions[book] = quantity;
	}

	// Get position has table.
	const map<string, long> & GetPositions()
	{
		return positions;
	}

	// Print position info.
	void Print();

};

template<typename T>
void Position<T>::Print()
{
	std::cout << "Bond: ";
	product.Print();
	std::cout << "; ";

	for (auto& pair : positions)
		std::cout << "book: " << pair.first << ", position: " << pair.second << "; ";
}


/**
 * Position Service to manage positions across multiple books and securities.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public Service<string,Position <T> >
{
public:
	// Add a trade to the service
	virtual void BookTrade(const Trade<T> &trade) = 0;

};


#endif
