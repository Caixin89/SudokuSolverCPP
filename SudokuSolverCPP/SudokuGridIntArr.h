#pragma once
#include "BaseSudokuGrid.h"
#include <algorithm>
class SudokuGridIntArr :
	public BaseSudokuGrid
{
private:
	unsigned char _grid[_side][_side];
public:
	SudokuGridIntArr();
	SudokuGridIntArr(const SudokuGridIntArr& x);
	virtual int Get(int y, int x) const;
	virtual void Set(int y, int x, int val);
};

