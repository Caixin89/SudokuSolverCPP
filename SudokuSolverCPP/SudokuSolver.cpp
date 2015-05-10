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
	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_inputFile >> _grid[i][j];
		}
	}
}

void SudokuSolver::Check_From_Row(int &aProb, int aGrid[][_side], int y, int x)
{
	for (int i = 0; i < _side; ++i)
	{
		if (i != x && aGrid[y][i] != 0)
			aProb &= ~(1 << aGrid[y][i]);
	}
}

void SudokuSolver::Check_From_Col(int &aProb, int aGrid[][_side], int y, int x)
{
	for (int i = 0; i < _side; ++i)
	{
		if (i != y && aGrid[i][x] != 0)
			aProb &= ~(1 << aGrid[i][x]);
	}
}

void SudokuSolver::Check_From_3x3(int &aProb, int aGrid[][_side], int y, int x)
{
	for (int y_start = y / 3 * 3; y_start < (y / 3 + 1) * 3; ++y_start)
	{
		for (int x_start = x / 3 * 3; x_start < (x / 3 + 1) * 3; ++x_start)
		{
			if ((y_start != y || x_start != x) && aGrid[y_start][x_start] != 0)
				aProb &= ~(1 << aGrid[y_start][x_start]);
		}
	}
}

void SudokuSolver::PrintGrid(int aGrid[][_side])
{
	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_solutionFile << aGrid[i][j] << " ";
		}

		_solutionFile << endl;
	}

	auto newEndTime = chrono::high_resolution_clock::now();
	_solutionFile << "Time taken for this solution: " << chrono::duration_cast<chrono::microseconds>(newEndTime - _endTime).count() << " microsec" << endl;
	_endTime = newEndTime;
	_solutionFile << "Time elapsed: " << chrono::duration_cast<chrono::microseconds>(_endTime - _startTime).count() << " microsec" << endl;
}

void SudokuSolver::RecurrSolve(int aGrid[][_side], int y, int x)
{
	int prob;
	int lsb;
	int copyGrid[_side][_side];
	copy(&aGrid[0][0], &aGrid[0][0] + _side * _side, &copyGrid[0][0]);

	for (; y < _side; ++y)
	{
		for (; x < _side; ++x)
		{
			prob = 1022;
			Check_From_Row(prob, copyGrid, y, x);
			Check_From_Col(prob, copyGrid, y, x);
			Check_From_3x3(prob, copyGrid, y, x);

			if (_grid[y][x] == 0)
			{
				if (prob != 0 && (prob & (prob - 1)) == 0)
					copyGrid[y][x] = CustomLog2(prob);
				else
				{
					while (prob != 0)
					{
						lsb = prob & -prob;
						copyGrid[y][x] = CustomLog2(lsb);
						RecurrSolve(copyGrid, y, x + 1);
						prob &= ~lsb;						
					}

					return;
				}
			}
		}

		x = 0;
	}

	PrintGrid(copyGrid);
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
		ans = (int) log2(val);
		break;
	}

	return ans;
}

void SudokuSolver::Solve()
{
	_endTime = _startTime = chrono::high_resolution_clock::now();
	RecurrSolve(_grid, 0, 0);
}