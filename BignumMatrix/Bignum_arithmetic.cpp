#include "stdafx.h"
#include "Bignum_arithmetic.h"
#include <cctype>
#include <algorithm>
#include <complex>
#include <chrono>

#define atoi myatoi

using namespace std;

const int Bignum_arithmetic::_BASE = 1000;
const int Bignum_arithmetic::_DIGITS_COUNT = to_string(_BASE).length() - 1;

int myatoi(const string& str)
{
	stringstream ss(str);
	int i;

	if ((ss >> i).fail() || !(ss >> ws).eof())
	{
		throw std::bad_cast();
	}
	return i;
}

void Bignum_arithmetic::initBigNum(string s)
{
	_isNegative = false;
	formatString(s);
	for (int i = (int)s.length(); i > 0; i -= _DIGITS_COUNT)
	{
		string block;
		if (i < _DIGITS_COUNT)
			block = s.substr(0, i);
		else
			block = s.substr(i - _DIGITS_COUNT, _DIGITS_COUNT);
		try
		{
			_a.push_back(atoi(block));
		}
		catch (...)
		{
			throw invalid_argument("Error while converting to integer.\nWrong argument:" + s);
		}
	}
}

void Bignum_arithmetic::formatString(string& s)
{
	string result;
	bool digitsStarted = false;
	s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
	for (char c : s)
	{
		if (!isdigit(c))
		{
			if (!digitsStarted && !_isNegative && c == '-')
				_isNegative = true;
			else
				throw invalid_argument("Error while converting to integer.\nWrong argument:" + s);
		}
		else
			digitsStarted = true;
	}
	if (_isNegative)
		s = s.substr(1, s.size() - 1);
}

void Bignum_arithmetic::deleteFrontNulls(Bignum_arithmetic& num)
{
	while (num._a.size() > 1 && num._a.back() == 0)
		num._a.pop_back();
}

Bignum_arithmetic::Bignum_arithmetic()
{
}

Bignum_arithmetic::Bignum_arithmetic(const string& strNumber)
{
	initBigNum(strNumber);
}

Bignum_arithmetic::Bignum_arithmetic(const long long& number)
{
	initBigNum(to_string(number));
}

Bignum_arithmetic::Bignum_arithmetic(const int& number)
{
	initBigNum(to_string(number));
}


Bignum_arithmetic::~Bignum_arithmetic() {}

string Bignum_arithmetic::toString() const
{
	if (*this == 0)
		return "0";
	string format = string("%0") + to_string(_DIGITS_COUNT) + string("d");
	string stringNumber = _isNegative ? "-" : "";
	char* buff = new char[_a.size() * 9 + 1];
	sprintf_s(buff, sizeof(buff), "%d", _a.empty() ? 0 : _a.back());
	stringNumber += buff;
	for (int i = (int)_a.size() - 2; i >= 0; --i)
	{
		sprintf_s(buff, sizeof(buff), format.c_str(), _a[i]);
		stringNumber += buff;
	}
	delete[] buff;
	return stringNumber;
}

Bignum_arithmetic::operator string() const
{
	return (*this).toString();
}

Bignum_arithmetic Bignum_arithmetic::operator=(const int& b) const
{
	return Bignum_arithmetic(to_string(b));
}

Bignum_arithmetic Bignum_arithmetic::operator=(const long long& b) const
{
	return Bignum_arithmetic(to_string(b));
}

Bignum_arithmetic Bignum_arithmetic::operator=(const Bignum_arithmetic& b)
{
	if (this == &b)
		return *this;
	_a = b._a;
	_isNegative = b._isNegative;
	return *this;
}

bool Bignum_arithmetic::operator==(int b) const
{
	for (int i = 0; i < _a.size(); ++i)
	{
		if (b % _BASE != _a[i])
			return false;
		b /= _BASE;
	}
	return true;
}

bool Bignum_arithmetic::operator==(const Bignum_arithmetic& b) const
{
	if ((_isNegative != b._isNegative) || (_a.size() != b._a.size() && _a[_a.size() - 1] != 0 && b._a[b._a.size() - 1] != 0))
		return false;
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		if (_a[i] != b._a[i])
			return false;
	}
	return true;
}

bool Bignum_arithmetic::operator!=(int b) const
{
	return !(*this == b);
}

bool Bignum_arithmetic::operator!=(const Bignum_arithmetic& b) const
{
	return !(*this == b);
}

bool Bignum_arithmetic::operator>(int b) const
{
	return *this > Bignum_arithmetic(to_string(b));
}

bool Bignum_arithmetic::operator>(const Bignum_arithmetic& b) const
{
	if (_isNegative != b._isNegative)
		return !_isNegative;
	if (_a.size() != b._a.size())// && _a[_a.size() - 1] != 0 && b._a[b._a.size() - 1] != 0)
		return _isNegative ? _a.size() < b._a.size() : _a.size() > b._a.size();
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		if (_a[i] != b._a[i])
			return _isNegative ? _a[i] < b._a[i] : _a[i] > b._a[i];
	}
	return false;
}

bool Bignum_arithmetic::operator>=(int b) const
{
	return *this >= Bignum_arithmetic(to_string(b));
}

bool Bignum_arithmetic::operator>=(const Bignum_arithmetic& b) const
{
	if (_isNegative != b._isNegative)
		return !_isNegative;
	if (_a.size() != b._a.size())// && _a[_a.size() - 1] != 0 && b._a[b._a.size() - 1] != 0)
		return _isNegative ? _a.size() < b._a.size() : _a.size() > b._a.size();
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		if (_a[i] != b._a[i])
			return _isNegative ? _a[i] < b._a[i] : _a[i] > b._a[i];
	}
	return true;
}

bool Bignum_arithmetic::operator<(int b) const
{
	return *this < Bignum_arithmetic(b);
}

bool Bignum_arithmetic::operator<(const Bignum_arithmetic& b) const
{
	if (_isNegative != b._isNegative)
		return _isNegative;
	if (_a.size() != b._a.size())// && _a[_a.size() - 1] != 0 && b._a[b._a.size() - 1] != 0)
		return _isNegative ? _a.size() > b._a.size() : _a.size() < b._a.size();
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		if (_a[i] != b._a[i])
			return _isNegative ? _a[i] > b._a[i] : _a[i] < b._a[i];
	}
	return false;
}

bool Bignum_arithmetic::operator<=(int b) const
{
	return *this <= Bignum_arithmetic(to_string(b));
}

bool Bignum_arithmetic::operator<=(const Bignum_arithmetic& b) const
{
	if (_isNegative != b._isNegative)
		return _isNegative;
	if (_a.size() != b._a.size())// && _a[_a.size() - 1] != 0 && b._a[b._a.size() - 1] != 0)
		return _isNegative ? _a.size() > b._a.size() : _a.size() < b._a.size();//think about it
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		if (_a[i] != b._a[i])
			return _isNegative ? _a[i] > b._a[i] : _a[i] < b._a[i];
	}
	return true;
}

Bignum_arithmetic Bignum_arithmetic::operator+(int b) const
{
	Bignum_arithmetic res = *this;
	if (_isNegative && b > 0)
		return -(-res - b);
	if (!_isNegative && b < 0)
		return res - (-b);
	if (res._isNegative && b < 0)
		b = -b;
	int pos = 0;
	res._a[0] += b;
	while (res._a[pos] >= _BASE)
	{
		if (pos == res._a.size() - 1)
			res._a.push_back(res._a[pos] / _BASE);
		else
			res._a[pos + 1] += res._a[pos] / _BASE;
		res._a[pos++] %= _BASE;
	}
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator+(const Bignum_arithmetic& b) const
{
	Bignum_arithmetic res = *this;
	if (res._isNegative && !b._isNegative)
		return b - (-res);
	if (!res._isNegative && b._isNegative)
		return res - (-b);
	int carry = 0;
	for (size_t i = 0; i<max(res._a.size(), b._a.size()) || carry; ++i) {
		if (i == res._a.size())
			res._a.push_back(0);
		res._a[i] += carry + (i < b._a.size() ? b._a[i] : 0);
		carry = res._a[i] >= _BASE;
		if (carry)  res._a[i] -= _BASE;
	}
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator-() const
{
	Bignum_arithmetic res = *this;
	res._isNegative = !_isNegative;
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator-(int b) const
{
	Bignum_arithmetic res = *this;
	if (_isNegative && b > 0)
		return -(-res + b);
	if (_isNegative && b < 0)
		return -(-res - (-b));
	if (!_isNegative && b < 0)
		return res + (-b);
	int pos = 0;
	res._a[0] -= b;
	bool stayPositive = *this >= b;
	while (res._a[pos] < 0)
	{
		if (pos == res._a.size() - 1)
		{
			res._isNegative = true;
			res._a.push_back((res._a[pos]) / _BASE);
		}
		else
			res._a[pos + 1] = ((res._a[pos] + res._a[pos + 1] * _BASE) / _BASE);
		res._a[pos] = res._a[pos] % _BASE + (stayPositive && res._a[pos] % _BASE < 0 ? _BASE : 0);
		if (!stayPositive)
		{
			res._a[pos] = -res._a[pos];
			if (res._a[pos + 1] > -_BASE)
			{
				res._isNegative = true;
				res._a[pos + 1] = -res._a[pos + 1];
				break;
			}
		}
		pos++;
	}
	deleteFrontNulls(res);
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator-(Bignum_arithmetic b) const
{
	Bignum_arithmetic res = *this;
	bool reversNegative = false;
	if ((res._isNegative && !b._isNegative) || (!res._isNegative && b._isNegative))
	{
		b._isNegative = !b._isNegative;
		return res + b;
	}
	if (res._isNegative && b._isNegative)
	{
		b._isNegative = false;
		res = b;
		b = *this;
	}
	if (b > res)
	{
		res = b;
		b = *this;
		reversNegative = true;
	}
	int carry = 0;
	for (size_t i = 0; i<min(b._a.size(), res._a.size()) || carry; ++i) {
		res._a[i] -= carry + (i < b._a.size() ? b._a[i] : 0);
		carry = res._a[i] < 0;
		if (carry) {
			if (i < res._a.size() - 1)
				res._a[i] += _BASE;
			else
			{
				res._a[i] = -res._a[i];
				res._isNegative = true;
				carry = false;
			}
		}
	}
	deleteFrontNulls(res);
	if (reversNegative)
		res._isNegative = !res._isNegative;
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator*(int b) const
{
	if (b >= _BASE)
		return *this * Bignum_arithmetic(to_string(b));

	Bignum_arithmetic res;
	res._a = lnum(_a.size() + 1);
	res._isNegative = _isNegative != (b < 0);
	b = std::abs(b);
	int carry = 0;
	for (int i = 0; i < _a.size(); ++i)
	{
		long long cur = res._a[i] + _a[i] * b + carry;
		res._a[i] = int(cur % _BASE);
		carry = int(cur / _BASE);
	}
	if (carry)
		res._a[_a.size()] = carry;
	deleteFrontNulls(res);
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator*(const Bignum_arithmetic& b) const
{
	Bignum_arithmetic res;
	res._a = lnum(_a.size() + b._a.size());
	for (size_t i = 0; i<_a.size(); ++i)
		for (int j = 0, carry = 0; j<(int)b._a.size() || carry; ++j) {
			long long cur = res._a[i + j] + _a[i] * 1ll * (j < (int)b._a.size() ? b._a[j] : 0) + carry;
			res._a[i + j] = int(cur % _BASE);
			carry = int(cur / _BASE);
		}
	deleteFrontNulls(res);
	res._isNegative = _isNegative != b._isNegative;
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator/(int b) const
{
	if (b == 0)
		throw overflow_error("Divide by zero exception");
	Bignum_arithmetic res;
	res._a = lnum(_a.size());
	res._isNegative = _isNegative != (b < 0);
	b = std::abs(b);
	long long ost = 0;
	for (int i = res._a.size() - 1; i >= 0; i--)
	{
		long long cur = ost * _BASE + _a[i];
		res._a[i] = cur / b;
		ost = cur % b;
	}
	deleteFrontNulls(res);
	return res;
}

Bignum_arithmetic Bignum_arithmetic::operator/(const Bignum_arithmetic& b) const
{
	if (b == 0)
		throw overflow_error("Divide by zero exception");
	if (_isNegative && b._isNegative)
		return (-*this) / (-b);
	if (_isNegative)
		return -((-*this) / b);
	if (b._isNegative)
		return -(*this / (-b));
	Bignum_arithmetic res = *this;
	Bignum_arithmetic curValue;
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		curValue._a.insert(curValue._a.begin(), 0);
		curValue._a[0] = _a[i];
		deleteFrontNulls(curValue);
		int x = 0;
		int l = 0, r = _BASE;
		while (l <= r)
		{
			int m = (l + r) >> 1;
			Bignum_arithmetic cur = b * m;
			if (cur <= curValue)
			{
				x = m;
				l = m + 1;
			}
			else
				r = m - 1;
		}
		res._a[i] = x;
		curValue = curValue - b * x;
	}
	deleteFrontNulls(res);

	return res;
}

int Bignum_arithmetic::operator%(const int& b) const
{
	if (b == 0)
		throw overflow_error("Divide by zero exception");
	int ost = 0;
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		int cur = ost * _BASE + _a[i];
		ost = cur % b;
	}
	return ost;
}

Bignum_arithmetic Bignum_arithmetic::operator%(const Bignum_arithmetic& b) const
{
	if (b == 0)
		throw overflow_error("Divide by zero exception");
	if (_isNegative && b._isNegative)
		return (-*this) % (-b);
	if (_isNegative)
		return ((-*this) % b);
	if (b._isNegative)
		return (*this % (-b));
	Bignum_arithmetic curValue;
	curValue._isNegative = b._isNegative;
	for (int i = _a.size() - 1; i >= 0; i--)
	{
		curValue._a.insert(curValue._a.begin(), 0);
		curValue._a[0] = _a[i];
		deleteFrontNulls(curValue);
		int x = 0;
		int l = 0, r = _BASE;
		while (l <= r)
		{
			int m = (l + r) >> 1;
			Bignum_arithmetic cur = b * m;
			if (cur <= curValue)
			{
				x = m;
				l = m + 1;
			}
			else
				r = m - 1;
		}
		curValue = curValue - b * x;
	}
	return curValue;
}

Bignum_arithmetic Bignum_arithmetic::abs(Bignum_arithmetic a)
{
	a._isNegative = false;
	return a;
}

Bignum_arithmetic Bignum_arithmetic::sqrt(Bignum_arithmetic a)
{
	if (a._isNegative)
		throw invalid_argument("Sqrt received negative number");
	Bignum_arithmetic l, r = a;
	Bignum_arithmetic res;
	while (l <= r)
	{
		Bignum_arithmetic m = (l + r) / 2;
		if (m*m <= a)
		{
			res = m;
			l = m + 1;
		}
		else
			r = m - 1;
	}
	return res;
}

Bignum_arithmetic Bignum_arithmetic::gcd(Bignum_arithmetic a, Bignum_arithmetic b)
{
	a = abs(a);
	b = abs(b);
	Bignum_arithmetic k("1");
	while ((a != 0) && (b != 0))
	{
		while ((a % 2 == 0) && (b % 2 == 0))
		{
			a = a / 2;
			b = b / 2;
			k = k * 2;
		}
		while (a % 2 == 0)
			a = a / 2;
		while (b % 2 == 0)
			b = b / 2;
		if (a >= b)
			a = a - b;
		else
			b = b - a;
	}
	return b*k;
}
