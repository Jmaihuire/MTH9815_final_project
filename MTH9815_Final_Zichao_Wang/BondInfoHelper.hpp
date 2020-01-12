// BondInfoHelper.hpp
// Created by Zichao Wang
// Date: Dec 8, 2018
// In this header file, I define several functions which
// can help me transform bond information.


#ifndef BONDINFOHELPER_HPP
#define BONDINFOHELPER_HPP

#include <string>


// From CUSIP get bond index (which is essentially the same,
// but easier to deal with.
int CUSIPToIndex(std::string CUSIP)
{
	if (CUSIP == "9128285Q9")
		return 0;
	else if (CUSIP == "9128285L0")
		return 1;
	else if (CUSIP == "9128285P1")
		return 2;
	else if (CUSIP == "9128285N6")
		return 3;
	else if (CUSIP == "9128285M8")
		return 4;
	else if (CUSIP == "912810SE9")
		return 5;

	return -1;
}


// From formatted price string to price number.
double CalculatePrice(std::string s)
{
	int size = s.size();

	//deal with all but first digits.
	double price = (double)(s[size - 1] - '0') / 256.0 + (double)(s[size - 2] - '0') / 32.0 + 10.0 * (double)(s[size - 3] - '0') / 32.0 + (double)(s[size - 5] - '0') + 10.0 * double(s[size - 6] - '0');
	
	// deal with first digit.
	if (size == 7)
		price += 100.0;

	return price;
}


// Convert price number into formatted string.
std::string PriceToPriceString(double price)
{
	std::string str;
	str += std::to_string(int(price));
	str += '-';
	double decimalPart = price - int(price);
	int xy = int(decimalPart * 32);
	if (xy < 10)
		str += "0";
	str += std::to_string(xy);
	decimalPart -= xy / 32.0;
	str += std::to_string(int(decimalPart * 256.0));
	return str;
}


#endif // !BONDINFOHELPER_HPP
