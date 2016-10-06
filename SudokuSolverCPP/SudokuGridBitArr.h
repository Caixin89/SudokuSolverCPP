#pragma once
#include "BaseSudokuGrid.h"
#include <algorithm>
class SudokuGridBitArr :
	public BaseSudokuGrid
{
private:
	unsigned long long _bitArr1[5];
	unsigned char _bitArr2;
public:
	SudokuGridBitArr();
	SudokuGridBitArr(const SudokuGridBitArr& x);
	virtual int Get(int y, int x) const;
	virtual void Set(int y, int x, int val);
};

