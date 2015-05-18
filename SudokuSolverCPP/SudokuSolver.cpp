#include "SudokuSolver.h"

char const * const SudokuSolver::_inputFileName = "sudoku.txt";
char const * const SudokuSolver::_solutionFileName = "solution.txt";

SudokuSolver::SudokuSolver()
{
	_inputFile.open(_inputFileName);
	_solutionFile.open(_solutionFileName);
	LoadGrid();
}

SudokuSolver::~SudokuSolver()
{
	_inputFile.close();
	_solutionFile.close();
}

void SudokuSolver::LoadGrid()
{
	int tmp;

	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_inputFile >> tmp;
			_grid.Set(i, j, tmp);
		}
	}
}

void SudokuSolver::Check_From_Row(int &aProb, const SudokuGridIntArr& aGrid, int y, int x)
{
	int tmp;

	for (int i = 0; i < _side; ++i)
	{
		tmp = aGrid.Get(y, i);

		if (i != x && tmp != 0)
			aProb &= ~(1 << tmp);
	}
}

void SudokuSolver::Check_From_Col(int &aProb, const SudokuGridIntArr& aGrid, int y, int x)
{
	int tmp;
	for (int i = 0; i < _side; ++i)
	{
		tmp = aGrid.Get(i, x);

		if (i != y && tmp != 0)
			aProb &= ~(1 << tmp);
	}
}

void SudokuSolver::Check_From_3x3(int &aProb, const SudokuGridIntArr& aGrid, int y, int x)
{
	int tmp;

	for (int y_start = y / 3 * 3; y_start < (y / 3 + 1) * 3; ++y_start)
	{
		for (int x_start = x / 3 * 3; x_start < (x / 3 + 1) * 3; ++x_start)
		{
			tmp = aGrid.Get(y_start, x_start);

			if ((y_start != y || x_start != x) && tmp != 0)
				aProb &= ~(1 << tmp);
		}
	}
}

void SudokuSolver::PrintGrid(const SudokuGridIntArr& aGrid)
{
	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_solutionFile << aGrid.Get(i, j) << " ";
		}

		_solutionFile << endl;
	}

	auto newEndTime = chrono::high_resolution_clock::now();
	_solutionFile << "Time taken for this solution: " << TimeStr(chrono::duration_cast<chrono::microseconds>(newEndTime - _endTime).count()) << endl;
	_endTime = newEndTime;
	_solutionFile << "Time elapsed: " << TimeStr(chrono::duration_cast<chrono::microseconds>(_endTime - _startTime).count()) << endl << endl;
}

void SudokuSolver::RecurrSolve(SudokuGridIntArr aGrid, int y, int x)
{
	int prob;
	int lsb;

	for (; y < _side; ++y)
	{
		for (; x < _side; ++x)
		{
			prob = 1022;
			Check_From_Row(prob, aGrid, y, x);
			Check_From_Col(prob, aGrid, y, x);
			Check_From_3x3(prob, aGrid, y, x);

			if (aGrid.Get(y, x) == 0)
			{
				if (prob != 0 && (prob & (prob - 1)) == 0)
					aGrid.Set(y, x, CustomLog2(prob));
				else
				{
					while (prob != 0)
					{
						lsb = prob & -prob;
						aGrid.Set(y, x, CustomLog2(lsb));
						RecurrSolve(aGrid, y, x + 1);
						prob &= ~lsb;
					}

					return;
				}
			}
		}

		x = 0;
	}

	PrintGrid(aGrid);
}

int SudokuSolver::CustomLog2(int val)
{
	int ans;

	switch (val)
	{
	case 1:
		ans = 0;
		break;
	case 2:
		ans = 1;
		break;
	case 4:
		ans = 2;
		break;
	case 8:
		ans = 3;
		break;
	case 16:
		ans = 4;
		break;
	case 32:
		ans = 5;
		break;
	case 64:
		ans = 6;
		break;
	case 128:
		ans = 7;
		break;
	case 256:
		ans = 8;
		break;
	case 512:
		ans = 9;
		break;
	default:
		ans = (int)log2(val);
		break;
	}

	return ans;
}

void SudokuSolver::Solve()
{
	_endTime = _startTime = chrono::high_resolution_clock::now();
	RecurrSolve(_grid, 0, 0);
}

string SudokuSolver::TimeStr(long long timeMicro)
{
	ostringstream oss;
	long long min, sec, ms;
	timeMicro -= (min = timeMicro / 60000000) * 60000000;
	timeMicro -= (sec = timeMicro / 1000000) * 1000000;
	timeMicro -= (ms = timeMicro / 1000) * 1000;
	oss << min << " min " << sec << " sec " << ms << " millisec " << timeMicro << " microSec";
	return oss.str();
}