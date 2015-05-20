#pragma once
class BaseSudokuGrid
{
public:
	static const int _side = 9;
	virtual int Get(int y, int x) const = 0;
	virtual void Set(int y, int x, int val) = 0;
	virtual void GetCopy(BaseSudokuGrid*& x) = 0;
};