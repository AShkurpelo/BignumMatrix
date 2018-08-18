#include "stdafx.h"
#include "UserInterface.h"
#include "Tests.h"
#include <iomanip>
#include <sstream>

using namespace std;

#define MATRIX_ARGUMENT 1
#define FRACTION_ARGUMENT 2
#define NUMBER_ARGUMENT 3
#define BACK_ARGUMENT 4

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::runTests()
{
	Tests::Tests tests;

	tests.bignum_add(true);// passed
	tests.bignum_sub(true);// passed
	tests.bignum_div(true);// passed
	tests.bignum_mod(true);// passed
	tests.bignum_mult(true);// passed	
	tests.bignum_sqrt(true);//passed
	tests.bignum_gcd(true);//passed

	system("pause");
}

void UserInterface::showStartMessage() const
{
	cout << "\n\t\t\tLong arithmetic in matrix use\n\n\n";
}

void UserInterface::printLibrary()
{
	printf("\n%s\nMatrix library (%d):\n", string(100, '-').c_str(), library.size());
	for (auto m : library)
	{
		printf("\t%s\n", m.first.c_str());
	}
}

bool UserInterface::mainScreen()
{
	while (true)
	{
		printLibrary();
		printf("\n%s\nCommands:\n   1 - Add or overwrite matrix\n   2 - Chose matrix\n   3 - Remove matrix\n   4 - Exit\n", string(100, '-').c_str());
		string chosenMatrix;
		auto choice = menuChoose(4);
		switch (choice)
		{
		case 1:
			addToLibraryScreen();
			break;
		case 2:
			if (choseFromLibraryScreen(chosenMatrix))
				operationsScreen(library[chosenMatrix], chosenMatrix);
			break;
		case 3:
			removeFromLibraryScreen();
			break;
		case 4:
			return true;
		}
	}
	return true;
}

bool UserInterface::addToLibraryScreen()
{
	Matrix toAdd;
	if (!initMatrix(toAdd))
		return false;
	addToLibrary(toAdd);
	return true;
}

string UserInterface::addToLibrary(Matrix& toAdd)
{
	string name;
	bool isNotNew = choseMatrixNameScreen(name);
	library[name] = toAdd;
	string result = isNotNew ? "overwritten" : "added";
	printf("\nMatrix %s %s", name.c_str(), result.c_str());
	return name;
}

bool UserInterface::choseFromLibraryScreen(string& chosenName)
{
	while (true)
	{
		if (!choseMatrixNameScreen(chosenName))
		{
			cout << "There is no matrix with such name.\n";
			if (tryAgain() == 'N')
				return false;
		}
		else
		{
			break;
		}
	}
	return true;
}

bool UserInterface::removeFromLibraryScreen()
{
	string name;
	if (!choseFromLibraryScreen(name))
		return false;
	library.erase(name);
	return true;
}

bool UserInterface::operationsScreen(Matrix matrix, string name = "<no_name>")
{
	while (true)
	{
		printf("\n%s\nCurrent matrix - %s\n\nOperations:\n   1 - Print grid\n   2 - Print each element\n   3 - Add\n   4 - Subtraction\n   5 - Multiplication\n   6 - Devisiion\n   7 - Frobenius form\n   8 - Back to main menu\n", string(100, '-').c_str(), name.c_str());
		Matrix matrixArg;
		Fraction fractionArg;
		Bignum_arithmetic bnumArg;
		function<Matrix()> operation;
		bool isOperationSet = false;

		auto choice = menuChoose(8);
		switch (choice)
		{
		case 1:
			print(matrix);
			break;
		case 2:
			print(matrix, true);
			break;
		case 3:
			printf("\n%s\nMatrix to add:\n", string(100, '-').c_str());
			if (!getMatrixArgumentScreen(matrixArg))
				break;

			operation = [&matrix, &matrixArg]() -> Matrix {return matrix + matrixArg; };
			isOperationSet = true;
			break;
		case 4:
			printf("\n%s\nMatrix to substract:\n", string(100, '-').c_str());
			if (!getMatrixArgumentScreen(matrixArg))
				break;

			operation = [&matrix, &matrixArg]() -> Matrix {return matrix - matrixArg; };
			isOperationSet = true;
			break;
		case 5:
			isOperationSet = argumentChoseScreen(operation, matrix, matrixArg, fractionArg, bnumArg);
			break;
		case 6:
			isOperationSet = argumentChoseScreen(operation, matrix, matrixArg, fractionArg, bnumArg, false);
			break;
		case 7:
		{
			Fraction res = ~matrix;
			print(res);
			return true;
		}
		case 8:
			return true;
		}
		if (isOperationSet && !performOperation(operation, matrix, name))
			return true;
	}
}

bool UserInterface::argumentChoseScreen(function<Matrix()>& operation, Matrix& matrix, Matrix& matrixArg, Fraction& fraction, Bignum_arithmetic& bnum, const bool withMatrix)
{
	int selectedMenuItem;
	if (withMatrix)
	{
		printf("\n%s\nChose argument type:\n\nOperations:\n   1 - Matrix\n   2 - Fraction\n   3 - Number\n   4 - Back\n", string(100, '-').c_str());
		selectedMenuItem = menuChoose(4);
	}
	else
	{
		printf("\n%s\nChose argument type:\n\nOperations:\n   1 - Fraction\n   2 - Number\n   3 - Back\n", string(100, '-').c_str());
		selectedMenuItem = menuChoose(3) + 1;
	}
	switch (selectedMenuItem)
	{
	case MATRIX_ARGUMENT:
		if (!getMatrixArgumentScreen(matrixArg))
			return false;

		operation = [&matrix, &matrixArg]() -> Matrix {return matrix * matrixArg; };
		return true;
		break;
	case FRACTION_ARGUMENT:
		if (!inputFraction(fraction))
			return false;

		operation = [&matrix, &fraction]() -> Matrix {return matrix * fraction; };
		return true;
		break;
	case NUMBER_ARGUMENT:
		if (!inputBigNum(bnum))
			return false;

		operation = [&matrix, &bnum]() -> Matrix {return matrix * bnum; };
		return true;
		break;
	case BACK_ARGUMENT:
		return false;
	};
	return false;
}


bool UserInterface::performOperation(function<Matrix()> operation, Matrix& matrix, string& name)
{
	cout << "\nCalculating...";
	Matrix result;
	try
	{
		result = operation();
		cout << "done\n\n";
		if (!resultScreen(result, matrix, name))
			return false;
	}
	catch (const runtime_error& re)
	{
		cout << endl << "Exception: " << re.what() << endl << endl;
		return true;
	}
	catch (const exception& ex)
	{
		cout << endl << "Exception: " << ex.what() << endl << endl;
		return true;
	}
	return true;
}

bool UserInterface::resultScreen(Matrix& result, Matrix& current, string& name)
{
	printf("\n%s\nResult matrix:\n\nOperations:\n   1 - Add to library\n   2 - Operations\n", string(100, '-').c_str());
	auto choice1 = menuChoose(2);
	switch (choice1)
	{
	case 1:
	{
		name = addToLibrary(result);
		cout << "\n\nContinue working with result matrix:\n\nOperations:\n   1 - Yes\n   2 - No\n";
		auto choice2 = menuChoose(2);
		switch (choice2)
		{
		case 1:
			current = result;
			break;
		case 2:
			return false;
		}
		break;
	}
	case 2:
		name = "<no_name>";
		current = result;
		break;
	}
	return true;
}

int UserInterface::menuChoose(int count)
{
	int res;
	string s;
	while (true)
	{
		printf("\ncommand:");
		cin >> s;
		try
		{
			res = atoi(s.c_str());
			if (res > 0 && res <= count)
				return res;
			throw exception();
		}
		catch (...)
		{
			printf("Wrong command\n");
		}
	}
}

bool UserInterface::getMatrixArgumentScreen(Matrix& argument)
{
	while (true)
	{
		cout << "\n\nOperations:\n   1 - Chose from library\n   2 - Input new\n   3 - Back\n";
		auto choice = menuChoose(3);
		switch (choice)
		{
		case 1:
		{
			string chosenMatrix;
			if (!choseFromLibraryScreen(chosenMatrix))
				break;
			argument = library[chosenMatrix];
			return true;
		}
		case 2:
			if (!initMatrix(argument))
				break;
			return true;
		case 3:
			return false;
		}
	}
}

bool UserInterface::initMatrix(Matrix& toInit)
{
	if (!inputMatrixSize(toInit))
		return false;

	cout << "\n\nChose matrix`s grid input type:\n\nOperations:\n   1 - Manually\n   2 - By random\n";
	auto choice = menuChoose(2);
	if (choice == 1)
	{
		return inputMatrixGrid(toInit);
	}
	string errorMessage;
	if (!toInit.initGridByRandom(errorMessage))
	{
		cout << errorMessage << endl;
		return false;
	}
	return true;
}

bool UserInterface::inputMatrixSize(Matrix& m)
{
	int x, y;
	printf("\n%s\nInput matrix`s size:\n", string(100, '-').c_str());
	char loop = 'Y';
	while (loop == 'Y')
	{
		try
		{
			cout << "\nColumns count (x):";
			cin >> x;
			cout << "\nRows count (y):";
			cin >> y;
			m = Matrix(x, y);
			break;
		}
		catch (...)
		{
			cout << endl << "Exception: Error while converting to unsigned int" << endl << endl;
			loop = tryAgain();
			if (loop == 'N')
				return false;
		}
	}
	return true;
}

bool UserInterface::inputMatrixGrid(Matrix& m)
{
	for (size_t i = 0; i < m.getY(); ++i)
		for (size_t j = 0; j < m.getX(); ++j)
		{
			char loop = 'Y';
			while (loop == 'Y')
			{
				char* buff = new char[256];
				sprintf_s(buff, 256, "\nInput numbers m and n for fraction (m/n) at position (%d, %d):\n\n\tm:", j, i);
				cout << buff;
				delete[] buff;
				string numm, numn;
				cin >> numm;
				cout << "\n\tn:";
				cin >> numn;
				try
				{
					m.grid[i][j] = Fraction(numm, numn);
					loop = 'N';
				}
				catch (const runtime_error& re)
				{
					cout << endl << "Exception: " << re.what() << endl << endl;
					loop = tryAgain();
					if (loop == 'N')
						return false;
				}
				catch (const exception& ex)
				{
					cout << endl << "Exception: " << ex.what() << endl << endl;
					loop = tryAgain();
					if (loop == 'N')
						return false;
				}
			}
		}
	return true;
}

bool UserInterface::initMatrixGridByRandom(Matrix& matrix)
{
	try
	{
		const size_t maxStringSize = 50;
		for (size_t i = 0; i < matrix.getY(); ++i)
			for (size_t j = 0; j < matrix.getX(); ++j)
			{
				string m = rand() % 2 == 1 ? "-" : "",
					n = rand() % 2 == 1 ? "-" : "";
				for (size_t t = 1; t <= 1 + rand() % maxStringSize; ++t)
				{
					m += to_string(rand() % 10);
				}
				for (size_t t = 1; t <= 1 + rand() % maxStringSize; ++t)
				{
					n += to_string(rand() % 10);
				}
				matrix.grid[i][j] = Fraction(m, n);
			}
	}
	catch (const runtime_error& re)
	{
		cout << endl << "Exception: " << re.what() << endl << endl;
		return false;
	}
	catch (const exception& ex)
	{
		cout << endl << "Exception: " << ex.what() << endl << endl;
		return false;
	}
	return true;
}

bool UserInterface::inputFraction(Fraction& fract)
{
	string numm, numn;
	cout << "\n\nInput numbers m and n for fraction (m/n):\n\n\tm:";
	cin >> numm;
	cout << "\n\tn:";
	cin >> numn;
	try
	{
		fract = Fraction(numm, numn);
		return true;
	}
	catch (const runtime_error& re)
	{
		cout << endl << "Exception: " << re.what() << endl << endl;
		return false;
	}
	catch (const exception& ex)
	{
		cout << endl << "Exception: " << ex.what() << endl << endl;
		return false;
	}
	catch (...)
	{
		cout << "\nUnknown exception.\n\n";
	}
}

bool UserInterface::inputBigNum(Bignum_arithmetic& bigNum)
{
	cout << "\n\nnumber:";
	string number;
	cin >> number;
	try
	{
		bigNum = Bignum_arithmetic(number);
	}
	catch (invalid_argument& ex)
	{
		cout << endl << "Exception: " << ex.what() << endl << endl;
		return false;
	}
}

char UserInterface::tryAgain() const
{
	char loop = 'X';
	while (loop != 'Y' && loop != 'N')
	{
		cout << "\n\nTry again or exit? (y/n):";
		cin >> loop;
		loop = toupper(loop);
	}
	return loop;
}

bool UserInterface::choseMatrixNameScreen(string& name)
{
	printf("\nmatrix`s name:");
	cin >> name;
	return library.find(name) != library.end();
}

void UserInterface::print(const Bignum_arithmetic& a)
{
	cout << "\n\nNumber:\n";
	cout << a.toString() << endl << endl;
}

void UserInterface::print(const Fraction& a) const
{
	cout << "\n\nFraction:\n";
	auto lines = a.getPrintableLines();
	for (string line : lines)
	{
		cout << line << endl;
	}
	cout << endl;
}

struct ElLines
{
	string line1, line2, line3;

	ElLines() {};
	ElLines(const string& line1, const string& line2, const string& line3)
		: line1(line1), line2(line2), line3(line3) {}
	ElLines(const vector<string>& lines)
	{
		if (lines.size() >= 3)
		{
			line1 = lines[0];
			line2 = lines[1];
			line3 = lines[2];
		}
	}
};

typedef vector<ElLines> MatrixRow;

void UserInterface::print(const Matrix& a, const bool eachElement) const
{
	cout << "\n\nMatrix:\n";
	if (eachElement)
	{
		for (size_t i = 0; i < a.getY(); ++i)
			for (size_t j = 0; j < a.getX(); ++j)
			{
				cout << "Element at position ( " + to_string(i) + ", " + to_string(j) + " ):";
				print(a.grid[i][j]);
			}
	}
	else
	{
		vector<MatrixRow> lines = vector<MatrixRow>(a.getY(), MatrixRow(a.getX()));
		vector<int> columnWidth(a.getX());
		for (size_t i = 0; i < a.getY(); ++i)
		{
			for (size_t j = 0; j < a.getX(); ++j)
			{
				lines[i][j] = a.grid[i][j].getPrintableLines();
				if (columnWidth[j] < lines[i][j].line1.length())
					columnWidth[j] = lines[i][j].line1.length();
			}
		}
		cout << endl;
		for (size_t i = 0; i < a.getY(); ++i)
		{
			stringstream line1, line2, line3;
			for (size_t j = 0; j < a.getX(); ++j)
			{
				line1 << setw(columnWidth[j] + 4) << internal << lines[i][j].line1;
				line2 << setw(columnWidth[j] + 4) << internal << lines[i][j].line2;
				line3 << setw(columnWidth[j] + 4) << internal << lines[i][j].line3;
			}
			cout << line1.str() << endl;
			cout << line2.str() << endl;
			cout << line3.str() << endl << endl;
		}
	}
	cout << endl << endl;
}

void UserInterface::run()
{
	showStartMessage();
	mainScreen();

	system("pause");
}
