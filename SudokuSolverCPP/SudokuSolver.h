#include <fstream>
#include <cmath>
#include <chrono>
using namespace std;

class SudokuSolver
{
private:
	ifstream _inputFile;
	ofstream _solutionFile;
	static const int _side = 9;
	static char const * const _inputFileName;
	static char const * const _solutionFileName;
	int _grid[_side][_side];
	chrono::system_clock::time_point _startTime, _endTime;

	void Check_From_Row(int &aProb, int aGrid[][_side], int y, int x);
	void Check_From_Col(int &aProb, int aGrid[][_side], int y, int x);
	void Check_From_3x3(int &aProb, int aGrid[][_side], int y, int x);
	void LoadGrid();
	void PrintGrid(int aGrid[][_side]);
	void RecurrSolve(int aGrid[][_side], int y, int x);
	int CustomLog2(int val);

public:
	SudokuSolver();
	~SudokuSolver();
	void Solve();
};