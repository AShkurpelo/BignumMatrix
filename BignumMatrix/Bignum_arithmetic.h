#pragma once
using namespace std;

class Bignum_arithmetic
{
	typedef vector<int> lnum;
	const static int _BASE;
	const static int _DIGITS_COUNT;

	lnum _a;
	bool _isNegative;

	void initBigNum(string);
	void formatString(string&);
	static void deleteFrontNulls(Bignum_arithmetic& a);
public:
	Bignum_arithmetic();
	Bignum_arithmetic(const string&);
	Bignum_arithmetic(const long long&);
	Bignum_arithmetic(const int&);
	~Bignum_arithmetic();

	string toString() const;
	operator string() const;
	Bignum_arithmetic operator = (const int& b) const;
	Bignum_arithmetic operator = (const long long& b) const;
	Bignum_arithmetic operator = (const Bignum_arithmetic& b);
	bool operator == (int b) const;
	bool operator == (const Bignum_arithmetic& b) const;
	bool operator != (int b) const;
	bool operator != (const Bignum_arithmetic& b) const;
	bool operator > (int b) const;
	bool operator > (const Bignum_arithmetic& b) const;
	bool operator >= (int b) const;
	bool operator >= (const Bignum_arithmetic& b) const;
	bool operator < (int b) const;
	bool operator < (const Bignum_arithmetic& b) const;
	bool operator <= (int b) const;
	bool operator <= (const Bignum_arithmetic& b) const;
	Bignum_arithmetic operator + (int b) const;
	Bignum_arithmetic operator + (const Bignum_arithmetic& b) const;
	Bignum_arithmetic operator - () const;
	Bignum_arithmetic operator - (int b) const;
	Bignum_arithmetic operator - (Bignum_arithmetic b) const;
	Bignum_arithmetic operator * (int b) const;
	Bignum_arithmetic operator * (const Bignum_arithmetic& b) const;
	Bignum_arithmetic operator / (int b) const;
	Bignum_arithmetic operator / (const Bignum_arithmetic& b) const;
	int operator % (const int& b) const;
	Bignum_arithmetic operator % (const Bignum_arithmetic& b) const;

	static Bignum_arithmetic abs(Bignum_arithmetic a);
	static Bignum_arithmetic sqrt(Bignum_arithmetic a);
	static Bignum_arithmetic gcd(Bignum_arithmetic a, Bignum_arithmetic b);
};

