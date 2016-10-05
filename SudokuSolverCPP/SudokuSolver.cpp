#include "SudokuSolver.h"

char const * const SudokuSolver::_inputFileName = "sudoku.txt";
char const * const SudokuSolver::_solutionFileName = "solution2.txt";

SudokuSolver::SudokuSolver()
{ 
	_grid = new SudokuGridIntArr();
}

SudokuSolver::~SudokuSolver()
{
	if (_inputFile.is_open())
		_inputFile.close();
	if (_solutionFile.is_open())
		_solutionFile.close();
	delete _grid;
}

bool SudokuSolver::LoadGrid()
{
	_inputFile.open(_inputFileName);
	_solutionFile.open(_solutionFileName);

	if (!_inputFile.is_open() || !_solutionFile.is_open())
		return false;

	int tmp;

	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_inputFile >> tmp;
			_grid->Set(i, j, tmp);
		}
	}

	return true;
}

void SudokuSolver::Check_From_Row(int &aProb, BaseSudokuGrid* aGrid, int y, int x)
{
	int tmp;

	for (int i = 0; i < _side; ++i)
	{
		tmp = aGrid->Get(y, i);

		if (i != x && tmp != 0)
			aProb &= ~(1 << tmp);
	}
}

void SudokuSolver::Check_From_Col(int &aProb, BaseSudokuGrid* aGrid, int y, int x)
{
	int tmp;
	for (int i = 0; i < _side; ++i)
	{
		tmp = aGrid->Get(i, x);

		if (i != y && tmp != 0)
			aProb &= ~(1 << tmp);
	}
}

void SudokuSolver::Check_From_3x3(int &aProb, BaseSudokuGrid* aGrid, int y, int x)
{
	int tmp;

	for (int y_start = y / 3 * 3; y_start < (y / 3 + 1) * 3; ++y_start)
	{
		for (int x_start = x / 3 * 3; x_start < (x / 3 + 1) * 3; ++x_start)
		{
			tmp = aGrid->Get(y_start, x_start);

			if ((y_start != y || x_start != x) && tmp != 0)
				aProb &= ~(1 << tmp);
		}
	}
}

void SudokuSolver::PrintGrid(BaseSudokuGrid* aGrid)
{
	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_solutionFile << aGrid->Get(i, j) << " ";
		}

		_solutionFile << endl;
	}

	auto newEndTime = high_resolution_clock::now();
	_solutionFile << "Time taken for this solution: " << TimeStr(duration_cast<microseconds>(newEndTime - _endTime).count()) << endl;
	_endTime = newEndTime;
	_solutionFile << "Time elapsed: " << TimeStr(duration_cast<microseconds>(_endTime - _startTime).count()) << endl << endl;
}

void SudokuSolver::RecurrSolve(BaseSudokuGrid* aGrid, int y, int x)
{
	int prob;
	int lsb;
	BaseSudokuGrid* copyGrid = aGrid->GetCopy();

	for (; y < _side; ++y)
	{
		for (; x < _side; ++x)
		{
			if (copyGrid->Get(y, x) == 0)
			{
				prob = 1022;
				Check_From_Row(prob, copyGrid, y, x);
				Check_From_Col(prob, copyGrid, y, x);
				Check_From_3x3(prob, copyGrid, y, x);

				if (prob != 0 && (prob & (prob - 1)) == 0)
					copyGrid->Set(y, x, log2(prob));
				else
				{
					while (prob != 0)
					{
						lsb = prob & -prob;
						copyGrid->Set(y, x, log2(lsb));
						RecurrSolve(copyGrid, y, x + 1);
						prob &= ~lsb;
					}

					delete copyGrid;
					return;
				}
			}
		}

		x = 0;
	}

	PrintGrid(copyGrid);
	delete copyGrid;
}

void SudokuSolver::Solve()
{
	_endTime = _startTime = high_resolution_clock::now();
	RecurrSolve(_grid, 0, 0);
}

string SudokuSolver::TimeStr(long long timeMicro)
{
	ostringstream oss;
	long long min, sec, ms;
	timeMicro -= (min = timeMicro / 60000000) * 60000000;
	timeMicro -= (sec = timeMicro / 1000000) * 1000000;
	timeMicro -= (ms = timeMicro / 1000) * 1000;
	oss << min << " min " << sec << " sec " << ms << " millisec " << timeMicro << " microsec";
	return oss.str();
}