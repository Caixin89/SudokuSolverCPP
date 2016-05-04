#pragma once
#include <fstream>
#include <cmath>
#include <chrono>
#include <sstream>
#include "SudokuGridBitArr.h"
#include "SudokuGridIntArr.h"
using namespace std;
using namespace chrono;

class SudokuSolver
{
private:
	ifstream _inputFile;
	ofstream _solutionFile;
	static const int _side = 9;
	static char const * const _inputFileName;
	static char const * const _solutionFileName;
	BaseSudokuGrid* _grid;
	high_resolution_clock::time_point _startTime, _endTime;

	void Check_From_Row(int &aProb, BaseSudokuGrid* aGrid, int y, int x);
	void Check_From_Col(int &aProb, BaseSudokuGrid* aGrid, int y, int x);
	void Check_From_3x3(int &aProb, BaseSudokuGrid* aGrid, int y, int x);
	void LoadGrid();
	void PrintGrid(BaseSudokuGrid* aGrid);
	void RecurrSolve(BaseSudokuGrid* aGrid, int y, int x);
	string TimeStr(long long timeMicro);

public:
	SudokuSolver();
	~SudokuSolver();
	void Solve();
};