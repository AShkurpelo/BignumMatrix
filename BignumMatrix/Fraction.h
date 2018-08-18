#pragma once
#include "Bignum_arithmetic.h"

class Fraction
{
	typedef Bignum_arithmetic bnum;

	bnum m, n;

	void reduce();
public:
	Fraction();
	Fraction(const bnum& m, const bnum& n);
	Fraction(const string& m, const string& n);
	Fraction(const long long& m, const long long& n);
	Fraction(const int& m, const int& n);
	~Fraction();

	Fraction operator = (const Fraction& b);
	Fraction operator + (const int& b);
	Fraction operator + (const bnum& b);
	Fraction operator + (const Fraction& b);
	Fraction operator - (const int& b);
	Fraction operator - (const bnum& b);
	Fraction operator - (const Fraction& b);
	Fraction operator * (const int& b);
	Fraction operator * (const bnum& b);
	Fraction operator * (const Fraction& b);
	Fraction operator / (const int& b);
	Fraction operator / (const bnum& b);
	Fraction operator / (const Fraction& b);

	static Fraction sqrt(const Fraction& a);

	bnum getM() const;
	bnum getN() const;
	void setM(const bnum& newM);
	void setN(const bnum& newN);

	vector<string> getPrintableLines() const;
};

