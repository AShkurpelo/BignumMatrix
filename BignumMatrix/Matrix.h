#pragma once
#include "Fraction.h"

using namespace std;

class Matrix
{
	typedef vector<Fraction> GridLine;
	typedef vector<GridLine> Grid;
	typedef Bignum_arithmetic BNum;

	size_t _x, _y;
public:
	Grid grid;

	Matrix();
	Matrix(size_t x, size_t y);
	~Matrix();

	Matrix operator = (const Matrix& b);
	Matrix operator + (const Matrix& b);
	Matrix operator - (const Matrix& b);
	Matrix operator * (const Matrix& b);
	Matrix operator * (const Fraction& b);
	Matrix operator * (const BNum& b);
	Matrix operator / (const Fraction& b);
	Matrix operator / (const BNum& b);
	Fraction operator ~ ();

	size_t getX() const;
	size_t getY() const;

	bool initGridByRandom(string& errorMessage);
};

