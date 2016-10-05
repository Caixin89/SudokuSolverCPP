#include "SudokuSolver.h"
#include <iostream>

int main()
{
	SudokuSolver ss;
	if (!ss.LoadGrid())
	{
		cout << "Unable to load sudoku from sudoku.txt or unable to open solution.txt for output!" << endl;
		cin.get();
		return 1;
	}
	ss.Solve();
	return 0;
}