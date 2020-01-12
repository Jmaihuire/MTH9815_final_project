/**
 * inquiryservice.hpp
 * Defines the data types and Service for customer inquiries.
 *
 * @author Breman Thuraisingham
 */

// Modified by Zichao Wang
// Date: Dec 21, 2018

#ifndef INQUIRY_SERVICE_HPP
#define INQUIRY_SERVICE_HPP

#include "Foundation/soa.hpp"
#include "MiddlePath/MiddlePathGeneral/tradebookingservice.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Various inqyury states
enum InquiryState { RECEIVED, QUOTED, DONE, REJECTED, CUSTOMER_REJECTED };

/**
 * Inquiry object modeling a customer inquiry from a client.
 * Type T is the product type.
 */
template<typename T>
class Inquiry
{
private:
    string inquiryId;
    T product;
    Side side;
    long quantity;
    double price;
    InquiryState state;

public:
    // ctor for an inquiry
    Inquiry() = default;

    Inquiry(string _inquiryId, const T &_product, Side _side, long _quantity, double _price, InquiryState _state) : product(_product)
    {
        inquiryId = _inquiryId;
        side = _side;
        quantity = _quantity;
        price = _price;
        state = _state;
    }

    // Get the inquiry ID
    const string& GetInquiryId() const
    {
        return inquiryId;
    }

    // Get the product
    const T& GetProduct() const
    {
        return product;
    }

    // Get the side on the inquiry
    Side GetSide() const
    {
        return side;
    }

    // Get the quantity that the client is inquiring for
    long GetQuantity() const
    {
        return quantity;
    }

    // Get the price that we have responded back with
    double GetPrice() const
    {
        return price;
    }

    // Get the current state on the inquiry
    InquiryState GetState() const
    {
        return state;
    }

    void SetInquiry(double _price, InquiryState _inquiryState)
    {
        price = _price;
        state = _inquiryState;
    }

    void Print()
    {
        std::string inquiryState;
        switch(state)
        {
            case RECEIVED : inquiryState = "RECEIVED"; break;
            case QUOTED : inquiryState = "QUOTED"; break;
            case DONE : inquiryState = "DONE"; break;
            case REJECTED : inquiryState = "REJECTED"; break;
            case CUSTOMER_REJECTED : inquiryState = "CUSTOMER_REJECTED";
        }

        std::cout
        << "inquiry ID: " << inquiryId
        << ", product" << product.GetProductId()
        << ", side: " << (side == BUY ? "buy" : "sell")
        << ", quantity: " << quantity
        << ", price: " << price
        << ", state: " << inquiryState << std::endl;
    }


};

/**
 * Service for customer inquirry objects.
 * Keyed on inquiry identifier (NOTE: this is NOT a product identifier since each inquiry must be unique).
 * Type T is the product type.
 */
template<typename T>
class InquiryService : public Service<string, Inquiry <T> >
{
public:
    // Send a quote back to the client
    virtual void SendQuote(const string &inquiryId, double price) = 0;

    // Reject an inquiry from the client
    virtual void RejectInquiry(const string &inquiryId) = 0;

};


#endif
