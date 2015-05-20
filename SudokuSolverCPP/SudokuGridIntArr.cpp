#include "SudokuGridIntArr.h"


SudokuGridIntArr::SudokuGridIntArr()
{
	for (int i = 0; i < _side; ++i)
	{
		for (int j = 0; j < _side; ++j)
		{
			_grid[i][j] = 0;
		}
	}
}

SudokuGridIntArr::SudokuGridIntArr(const SudokuGridIntArr& x)
{
	std::copy(&x._grid[0][0], &x._grid[0][0] + _side * _side, &_grid[0][0]);
}

int SudokuGridIntArr::Get(int y, int x) const
{
	return _grid[y][x];
}

void SudokuGridIntArr::Set(int y, int x, int val)
{
	_grid[y][x] = val;
}

void SudokuGridIntArr::GetCopy(BaseSudokuGrid*& x)
{
	x = new SudokuGridIntArr(*this);
}