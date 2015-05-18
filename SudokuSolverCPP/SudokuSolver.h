#pragma once
#include <fstream>
#include <cmath>
#include <chrono>
#include <sstream>
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
	SudokuGridIntArr _grid;
	chrono::system_clock::time_point _startTime, _endTime;

	void Check_From_Row(int &aProb, const SudokuGridIntArr& aGrid, int y, int x);
	void Check_From_Col(int &aProb, const SudokuGridIntArr& aGrid, int y, int x);
	void Check_From_3x3(int &aProb, const SudokuGridIntArr& aGrid, int y, int x);
	void LoadGrid();
	void PrintGrid(const SudokuGridIntArr& aGrid);
	void RecurrSolve(SudokuGridIntArr aGrid, int y, int x);
	int CustomLog2(int val);
	string TimeStr(long long timeMicro);

public:
	SudokuSolver();
	~SudokuSolver();
	void Solve();
};