#include "SudokuSolver.h"

char const * const SudokuSolver::_inputFileName = "sudoku.txt";
char const * const SudokuSolver::_solutionFileName = "solution.txt";

SudokuSolver::SudokuSolver()
{ 
	_grid = new SudokuGridIntArr();
	foundSolution = false;
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

void SudokuSolver::Check_From_Row(int &aProb, int y, int x)
{
	int tmp;

	for (int i = 0; i < _side; ++i)
	{
		tmp = _grid->Get(y, i);

		if (i != x && tmp != 0)
			aProb &= ~(1 << tmp);
	}
}

void SudokuSolver::Check_From_Col(int &aProb, int y, int x)
{
	int tmp;
	for (int i = 0; i < _side; ++i)
	{
		tmp = _grid->Get(i, x);

		if (i != y && tmp != 0)
			aProb &= ~(1 << tmp);
	}
}

void SudokuSolver::Check_From_3x3(int &aProb, int y, int x)
{
	int tmp;

	for (int y_start = y / 3 * 3; y_start < (y / 3 + 1) * 3; ++y_start)
	{
		for (int x_start = x / 3 * 3; x_start < (x / 3 + 1) * 3; ++x_start)
		{
			tmp = _grid->Get(y_start, x_start);

			if ((y_start != y || x_start != x) && tmp != 0)
				aProb &= ~(1 << tmp);
		}
	}
}

void SudokuSolver::PrintGrid()
{
	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_solutionFile << _grid->Get(i, j) << " ";
		}

		_solutionFile << endl;
	}
}

void SudokuSolver::RecurrSolve(int y, int x)
{
	int prob;
	int lsb;

	for (; y < _side; ++y)
	{
		for (; x < _side; ++x)
		{
			if (_grid->Get(y, x) == 0)
			{
				prob = 1022;
				Check_From_Row(prob, y, x);
				Check_From_Col(prob, y, x);
				Check_From_3x3(prob, y, x);

				while (prob != 0)
				{
					lsb = prob & -prob;
					_grid->Set(y, x, log2(lsb));
					RecurrSolve(y, x + 1);
					if (foundSolution)
						return;
					prob &= ~lsb;
				}

				_grid->Set(y, x, 0);
				return;
			}
		}

		x = 0;
	}

	PrintGrid();
	foundSolution = true;
}

void SudokuSolver::Solve()
{
	RecurrSolve(0, 0);
}
