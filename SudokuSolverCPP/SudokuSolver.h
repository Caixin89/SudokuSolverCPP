#pragma once
#include <fstream>
#include <cmath>
#include <sstream>
#include "SudokuGridBitArr.h"
#include "SudokuGridIntArr.h"
using namespace std;

class SudokuSolver
{
private:
	ifstream _inputFile;
	ofstream _solutionFile;
	static const int _side = 9;
	static char const * const _inputFileName;
	static char const * const _solutionFileName;
	BaseSudokuGrid* _grid;
	bool foundSolution;

	void Check_From_Row(int &aProb, int y, int x);
	void Check_From_Col(int &aProb, int y, int x);
	void Check_From_3x3(int &aProb, int y, int x);
	void PrintGrid();
	void RecurrSolve(int y, int x);

public:
	SudokuSolver();
	~SudokuSolver();
	void Solve();
	bool LoadGrid();
};