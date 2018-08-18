#include "stdafx.h"
#include "Fraction.h"
#include <algorithm>
#include <iomanip>

Fraction::Fraction()
{
	this->m = bnum(0);
	this->n = bnum(1);
}

Fraction::Fraction(const bnum& m, const bnum& n)
{
	this->m = bnum(m);
	this->n = bnum(n);
	reduce();
}

Fraction::Fraction(const string& m, const string& n)
{
	this->m = bnum(m);
	this->n = bnum(n);
	reduce();
}

Fraction::Fraction(const long long& m, const long long& n)
{
	this->m = bnum(m);
	this->n = bnum(n);
	reduce();
}

Fraction::Fraction(const int& m, const int& n)
{
	this->m = bnum(m);
	this->n = bnum(n);
	reduce();
}


Fraction::~Fraction()
{
}

Fraction Fraction::operator=(const Fraction& b)
{
	this->m = b.m;
	this->n = b.n;
	reduce();
	return *this;
}

Fraction Fraction::operator+(const int& b)
{
	Fraction res;
	res.m = m + n * b;
	res.n = n;
	res.reduce();
	return res;
}

Fraction Fraction::operator+(const bnum& b)
{
	Fraction res;
	res.m = m + n * b;
	res.n = n;
	res.reduce();
	return res;
}

Fraction Fraction::operator+(const Fraction& b)
{
	Fraction res;
	res.m = m*b.n + b.m*n;
	res.n = n*b.n;
	res.reduce();
	return res;
}

Fraction Fraction::operator-(const int& b)
{
	Fraction res;
	res.m = m - n * b;
	res.n = n;
	res.reduce();
	return res;
}

Fraction Fraction::operator-(const bnum& b)
{
	Fraction res;
	res.m = m - n * b;
	res.n = n;
	res.reduce();
	return res;
}

Fraction Fraction::operator-(const Fraction& b)
{
	Fraction res;
	res.m = m*b.n - b.m*n;
	res.n = n*b.n;
	res.reduce();
	return res;
}

Fraction Fraction::operator*(const int& b)
{
	Fraction res;
	res.m = m * b;
	res.n = n;
	res.reduce();
	return res;
}

Fraction Fraction::operator*(const bnum& b)
{
	Fraction res;
	res.m = m * b;
	res.n = n;
	res.reduce();
	return res;
}

Fraction Fraction::operator*(const Fraction& b)
{
	Fraction res;
	res.m = m*b.m;
	res.n = n*b.n;
	res.reduce();
	return res;
}

Fraction Fraction::operator/(const int& b)
{
	Fraction res;
	res.m = m;
	res.n = n * b;
	res.reduce();
	return res;
}

Fraction Fraction::operator/(const bnum& b)
{
	Fraction res;
	res.m = m;
	res.n = n * b;
	res.reduce();
	return res;
}

Fraction Fraction::operator/(const Fraction& b)
{
	Fraction res;
	res.m = m*b.n;
	res.n = n*b.m;
	res.reduce();
	return res;
}

vector<string> Fraction::getPrintableLines() const
{
	vector<string> res;
	bool isNegative = m < 0;
	string mStr = isNegative ? (-m).toString() : m.toString(),
		nStr = n.toString();
	int mLength = mStr.length(),
		nLength = nStr.length(),
		size = max(mLength, nLength),
		mBackOffset = (size - mLength) / 2,
		nBackOffset = (size - nLength) / 2,
		mFrontOffset = size - mLength - mBackOffset,
		nFrontOffset = size - nLength - nBackOffset;
	res.push_back(string(2 + mFrontOffset, ' ').append(mStr).append(string(mBackOffset, ' ')));
	res.push_back((isNegative ? "- " : "  ") + string(size, '-'));
	res.push_back(string(2 + nFrontOffset, ' ').append(nStr).append(string(nBackOffset, ' ')));
	return res;
}

Fraction Fraction::sqrt(const Fraction& a)
{
	Fraction res;
	res.m = Bignum_arithmetic::sqrt(a.m);
	res.n = Bignum_arithmetic::sqrt(a.n);
	res.reduce();
	return res;
}

Fraction::bnum Fraction::getM() const
{
	return m;
}

Fraction::bnum Fraction::getN() const
{
	return n;
}

void Fraction::setM(const bnum& newM)
{
	m = newM;
	reduce();
}

void Fraction::setN(const bnum& newN)
{
	n = newN;
	reduce();
}

void Fraction::reduce()
{
	m = (m < 0) != (n < 0) ? (m < 0 ? m : -m) : (m < 0 ? -m : m);
	n = n < 0 ? -n : n;
	bnum divider = Bignum_arithmetic::gcd(m, n);
	this->m = this->m / divider;
	this->n = this->n / divider;
}
