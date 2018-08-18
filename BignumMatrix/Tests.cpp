#include "stdafx.h"
#include "Tests.h"
#include "Bignum_arithmetic.h"
#include <ctime>
#include "UserInterface.h"

namespace Tests
{
	Tests::Tests()
	{
	}


	Tests::~Tests()
	{
	}

	void Tests::bignum_div(bool many)
	{
		cout << "\nTesting bignum operator '/':" << endl;
		if (many)
		{
			long long a = 456789741;
			bnum dev(to_string(a)), p;
			cout << dev.toString() << endl;
			for (int i = -100; i < 10000; ++i)
			{
				try
				{
					if (i == 0)
						throw overflow_error("Divide by zero exception");
					p = bnum(to_string(i));
					auto res = dev / p;
					auto resInt = dev / i;
					long long exp = a / i;
					if (res.toString() != to_string(exp) || resInt.toString() != to_string(exp))
					{
						cout << "i: " << i << endl;
						cout << "expected    : " << exp << endl;
						cout << "result      : " << res.toString() << endl;
						cout << "result (int): " << resInt.toString() << endl << endl;
					}
				}
				catch (overflow_error& ex)
				{
					cout << endl << "Exception: at i = " << i << endl << ex.what() << endl << endl;
				}
			}
		}
		else
		{

		}
	}

	void Tests::bignum_mod(bool many)
	{
		cout << "\nTesting bignum operator '%':" << endl;
		if (many)
		{
			long long a = 45678974651;
			bnum dev(to_string(a)), p;
			cout << dev.toString() << endl;
			for (int i = -100; i < 10000; ++i)
			{
				try
				{
					if (i == 0)
						throw overflow_error("Divide by zero exception");
					p = bnum(to_string(i));
					auto res = dev % p;
					auto resInt = dev % i;
					long long exp = a % i;
					if (res.toString() != to_string(exp) || resInt != exp)
					{
						cout << "i: " << i << endl;
						cout << "expected    : " << exp << endl;
						cout << "result      : " << res.toString() << endl;
						cout << "result (int): " << resInt << endl << endl;
					}
				}
				catch (overflow_error& ex)
				{
					cout << endl << "Exception: at i = " << i << endl << ex.what() << endl << endl;
				}
			}
		}
		else
		{

		}
	}

	void Tests::bignum_mult(bool many)
	{
		cout << "\nTesting bignum operator '*':" << endl;
		if (many)
		{
			long long a = 45678978;
			bnum dev(to_string(a)), p;
			cout << dev.toString() << endl;
			for (int i = -1000; i < 10000; ++i)
			{
				p = bnum(to_string(i));
				auto res = dev * p;
				long long exp = a * i;
				auto resInt = dev * i;
				if (res.toString() != to_string(exp) || resInt.toString() != to_string(exp))
				{
					cout << "i: " << i << endl;
					cout << "expected    : " << exp << endl;
					cout << "result      : " << res.toString() << endl;
					cout << "result (int): " << resInt.toString() << endl << endl;
				}
			}
		}
		else
		{

		}
	}

	void Tests::bignum_add(bool many)
	{
		cout << "\nTesting bignum operator '+':" << endl;
		if (many)
		{
			long long a = 45688;
			bnum dev(to_string(a)), p;
			cout << dev.toString() << endl;
			for (int i = -50000; i < 50000; ++i)
			{
				p = bnum(to_string(i));
				auto res = dev + p;
				long long exp = a + i;
				auto resInt = dev + i;
				if (res.toString() != to_string(exp) || resInt.toString() != to_string(exp))
				{
					cout << "i: " << i << endl;
					cout << "expected    : " << exp << endl;
					cout << "result      : " << res.toString() << endl;
					cout << "result (int): " << resInt.toString() << endl << endl;
				}
			}
		}
		else
		{

		}
	}

	void Tests::bignum_sub(bool many)
	{
		cout << "\nTesting bignum operator '-':" << endl;
		if (many)
		{
			long long a = 45978;
			bnum dev(to_string(a)), p;
			cout << dev.toString() << endl;
			for (int i = -50000; i < 50000; ++i)
			{
				p = bnum(to_string(i));
				auto res = dev - p;
				long long exp = a - i;
				auto resInt = dev - i;
				if (res.toString() != to_string(exp) || resInt.toString() != to_string(exp))
				{
					cout << "i: " << i << endl;
					cout << "expected    : " << exp << endl;
					cout << "result      : " << res.toString() << endl;
					cout << "result (int): " << resInt.toString() << endl << endl;
				}
			}
		}
		else
		{

		}
	}

	void Tests::bignum_sqrt(bool many)
	{
		cout << "\nTesting bignum function 'sqrt':" << endl;
		if (many)
		{
			bnum p;
			for (int i = -1; i < 10000; ++i)
			{
				try {
					p = bnum(to_string(i));
					auto res = bnum::sqrt(p);
					long long exp = (int)sqrt(i);
					if (res.toString() != to_string(exp))
					{
						cout << "i: " << i << endl;
						cout << "expected: " << exp << endl;
						cout << "result  : " << res.toString() << endl << endl;
					}
				}
				catch (invalid_argument& ex) {
					cout << endl << "Exception: at i = " << i << endl << ex.what() << endl << endl;
				}
			}
		}
		else
		{

		}
	}

	void Tests::bignum_gcd(bool many)
	{
		cout << "\nTesting bignum function 'gcd':" << endl;
		if (many)
		{
			bnum a("2331239408960");
			bnum b("54687897484561135489784545456487878121231534687845312561010044545");
			bnum c("37959494438756197120");
			bnum res = bnum::gcd(a, c);
			if (res != 3520)
			{
				cout << "gcd(a, c)" << endl;
				cout << "expected: " << 3520 << endl;
				cout << "result  : " << res.toString() << endl << endl;
			}
			res = bnum::gcd(a, b);
			if (res != 5)
			{
				cout << "gcd(a, b)" << endl;
				cout << "expected: " << 5 << endl;
				cout << "result  : " << res.toString() << endl << endl;
			}
			res = bnum::gcd(c, b);
			if (res != 5)
			{
				cout << "gcd(c, b)" << endl;
				cout << "expected: " << 5 << endl;
				cout << "result  : " << res.toString() << endl << endl;
			}
		}
		else
		{
			bnum a("2331239408960");
			bnum b("54687897484561135489784545456487878121231534687845312561010044545");
			bnum c("37959494438756197120");
			cout << bnum::gcd(a, c).toString();
		}
	}

	void Tests::bignum_sign()
	{
		cout << "\nTesting bignum signing:" << endl;
		try
		{
			cout << (Bignum_arithmetic("-37959494438756197120") * -5302).toString() << endl;
			cout << (Bignum_arithmetic("-37959494438756197120") * (Bignum_arithmetic(-5302))).toString() << endl;
			cout << (Bignum_arithmetic("-37959494438756197120") / -5302).toString() << endl;
			cout << (Bignum_arithmetic("-37959494438756197120") / (Bignum_arithmetic(-5302))).toString() << endl;
			cout << (Bignum_arithmetic("37959494438756197120") % 0) << endl;
			cout << (Bignum_arithmetic("37959494438756197120") % (Bignum_arithmetic(0))).toString() << endl;
		}
		catch (overflow_error& ex)
		{
			cout << endl << "Exception: " << ex.what() << endl << endl;
		}
	}
}
