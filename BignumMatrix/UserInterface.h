#pragma once
#include "Matrix.h"
#include <map>
#include "Tests.h"
#include <functional>

class UserInterface
{
private:
	map<string, Matrix> library;
	void printLibrary();

	bool mainScreen();
	bool addToLibraryScreen();
	string addToLibrary(Matrix& toAdd);
	bool choseFromLibraryScreen(string& chosenName);
	bool removeFromLibraryScreen();
	bool operationsScreen(Matrix matrix, string name);
	bool argumentChoseScreen(function<Matrix()>& operation, Matrix& matrix, Matrix& matrixArg, Fraction& fraction, Bignum_arithmetic& bnum, bool withMatrix = true);
	bool getMatrixArgumentScreen(Matrix& argument);
	bool resultScreen(Matrix& result, Matrix& current, string& name);
	bool performOperation(function<Matrix()> operation, Matrix& matrix, string& name);


	int menuChoose(int count);
	char tryAgain() const;
	bool choseMatrixNameScreen(string& name);

	bool initMatrix(Matrix& toInit);
	bool inputMatrixSize(Matrix& m);
	bool inputMatrixGrid(Matrix& m);
	bool initMatrixGridByRandom(Matrix& m);

	bool inputFraction(Fraction& fract);
	bool inputBigNum(Bignum_arithmetic& bigNum);

	void print(const Bignum_arithmetic& a);
	void print(const Fraction& a) const;
	void print(const Matrix& a, const bool eachElement = false) const;
	void showStartMessage() const;

public:
	UserInterface();
	~UserInterface();
	void run();
	void runTests();
};
