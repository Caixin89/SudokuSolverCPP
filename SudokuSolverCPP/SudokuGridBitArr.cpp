#include "SudokuGridBitArr.h"


SudokuGridBitArr::SudokuGridBitArr()
{
	_bitArr1[0] = 0;
	_bitArr1[1] = 0;
	_bitArr1[2] = 0;
	_bitArr1[3] = 0;
	_bitArr1[4] = 0;
	_bitArr2 = 0;
}

SudokuGridBitArr::SudokuGridBitArr(const SudokuGridBitArr& x)
{
	std::copy(&x._bitArr1[0], &x._bitArr1[4] + 1, &_bitArr1[0]);
	_bitArr2 = x._bitArr2;
}

int SudokuGridBitArr::Get(int y, int x) const
{
	int offset = y * _side + x;
	
	if (offset == _side * _side - 1)
		return _bitArr2;

	return (_bitArr1[offset / 16] >> (offset % 16 * 4)) & 0xF;
}

void SudokuGridBitArr::Set(int y, int x, int val)
{
	int offset = y * _side + x;
	val &= 0xF;

	if (offset == _side * _side - 1)
		_bitArr2 = val;
	else
	{
		int arrIdx = offset / 16;
		int bitIdx = offset % 16;
		_bitArr1[arrIdx] &= ~(0xFULL << (bitIdx * 4));
		_bitArr1[arrIdx] |= (((unsigned long long) val) << (bitIdx * 4));
	}
}

void SudokuGridBitArr::GetCopy(BaseSudokuGrid*& x)
{
	x = new SudokuGridBitArr(*this);
}