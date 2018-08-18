#include "stdafx.h"
#include "Matrix.h"
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>

Matrix::Matrix()
{
	this->_x = 0;
	this->_y = 0;
	grid = Grid(_y, GridLine(_x));
}

Matrix::Matrix(size_t x, size_t y)
{
	this->_x = x;
	this->_y = y;
	grid = Grid(y, GridLine(x));
}


Matrix::~Matrix()
{
}

Matrix Matrix::operator=(const Matrix& b)
{
	_x = b._x;
	_y = b._y;
	grid = b.grid;
	return *this;
}

Matrix Matrix::operator+(const Matrix& b)
{
	if (_x != b._x || _y != b._y)
		throw invalid_argument("Wrong matrix`s size for addition");
	Matrix res = *this;
	for (size_t i = 0; i < _y; ++i)
		for (size_t j = 0; j < _x; ++j)
			res.grid[i][j] = grid[i][j] + b.grid[i][j];
	return res;
}

Matrix Matrix::operator-(const Matrix& b)
{
	if (_x != b._x || _y != b._y)
		throw invalid_argument("Wrong matrix`s size for subtraction");
	Matrix res = *this;
	for (size_t i = 0; i < _y; ++i)
		for (size_t j = 0; j < _x; ++j)
			res.grid[i][j] = grid[i][j] - b.grid[i][j];
	return res;
}

Matrix Matrix::operator*(const Matrix& b)
{
	if (_y != b._x)
		throw invalid_argument("Wrong matrix`s size for multiplication");
	Matrix res(_x, b._y);
	for (size_t i = 0; i < b._y; ++i)
		for (size_t j = 0; j < _x; ++j)
			for (size_t t = 0; t < _y; ++t)
				res.grid[i][j] = res.grid[i][j] + grid[i][t] * b.grid[t][j];

	return res;
}

Matrix Matrix::operator*(const Fraction& b)
{
	Matrix res(_x, _y);
	for (size_t i = 0; i < _y; ++i)
		for (size_t j = 0; j < _x; ++j)
			res.grid[i][j] = grid[i][j] * b;
	return res;
}

Matrix Matrix::operator*(const BNum& b)
{
	Matrix res(_x, _y);
	for (size_t i = 0; i < _y; ++i)
		for (size_t j = 0; j < _x; ++j)
			res.grid[i][j] = grid[i][j] * b;
	return res;
}

Matrix Matrix::operator/(const Fraction& b)
{
	Matrix res(_x, _y);
	for (size_t i = 0; i < _y; ++i)
		for (size_t j = 0; j < _x; ++j)
			res.grid[i][j] = grid[i][j] / b;
	return res;
}

Matrix Matrix::operator/(const BNum& b)
{
	Matrix res(_x, _y);
	for (size_t i = 0; i < _y; ++i)
		for (size_t j = 0; j < _x; ++j)
			res.grid[i][j] = grid[i][j] / b;
	return res;
}

Fraction Matrix::operator~()
{
	Fraction res;
	for (size_t i = 0; i < _y; ++i)
		for (size_t j = 0; j < _x; ++j)
			res = res + grid[i][j] * grid[i][j];
	return Fraction::sqrt(res);
}

size_t Matrix::getX() const
{
	return this->_x;
}

size_t Matrix::getY() const
{
	return this->_y;
}

bool Matrix::initGridByRandom(string& errorMessage)
{
	try
	{
		const size_t maxStringSize = 50;
		for (size_t i = 0; i < _y; ++i)
			for (size_t j = 0; j < _x; ++j)
			{
				string m = rand() % 2 == 1 ? "-" : "",
					n = rand() % 2 == 1 ? "-" : "";
				int digitsCount = 1 + rand() % maxStringSize;
				for (size_t t = 1; t <= digitsCount; ++t)
				{
					m += to_string(rand() % 10);
				}
				digitsCount = 1 + rand() % maxStringSize;
				for (size_t t = 1; t <= digitsCount; ++t)
				{
					n += to_string(rand() % 10);
				}
				grid[i][j] = Fraction(m, n);
			}
	}
	catch (const runtime_error& re)
	{
		char* buff = new char[256];
		sprintf_s(buff, 256, "Exception: %s", re.what());
		errorMessage = buff;
		delete[] buff;
		return false;
	}
	catch (const exception& ex)
	{
		char* buff = new char[256];
		sprintf_s(buff, 256, "Exception: %s\n", ex.what());
		errorMessage = buff;
		delete[] buff;
		return false;
	}
	return true;
}