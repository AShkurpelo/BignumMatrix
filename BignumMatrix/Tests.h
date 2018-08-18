#pragma once
#include "Bignum_arithmetic.h"

namespace Tests
{

	class Tests
	{
		typedef Bignum_arithmetic bnum;
	public:
		Tests();
		~Tests();

		void bignum_div(bool many);
		void bignum_mod(bool many);
		void bignum_mult(bool many);
		void bignum_add(bool many);
		void bignum_sub(bool many);
		void bignum_sqrt(bool many);
		void bignum_gcd(bool many);
		void bignum_sign();
	};
}

