#include <iostream>

#include "sudoku.h"
#include "sudoku.hpp"

int main()
{
	// Example puzzle.
	int puzzle[9][9] = {
		{ 3, 0, 6,  5, 0, 8,  4, 0, 0 },
		{ 5, 2, 0,  0, 0, 0,  0, 0, 0 },
		{ 0, 8, 7,  0, 0, 0,  0, 3, 1 },

		{ 0, 0, 3,  0, 1, 0,  0, 8, 0 },
		{ 9, 0, 0,  8, 6, 3,  0, 0, 5 },
		{ 0, 5, 0,  0, 9, 0,  6, 0, 0 },
		
		{ 1, 3, 0,  0, 0, 0,  2, 5, 0 },
		{ 0, 0, 0,  0, 0, 0,  0, 7, 4 },
		{ 0, 0, 5,  2, 0, 6,  3, 0, 0 }
	};

	// Attempt to solve.
	if (solveSudoku(puzzle, 0, 0))
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
				std::cout << puzzle[i][j] << " ";
			std::cout << std::endl;
		}
	else
		std::cout << "\nNo solution found.\n";

	//
	//
	//
	Sudoku sudoku = Sudoku({ 
		3, 0, 6,  5, 0, 8,  4, 0, 0,
		5, 2, 0,  0, 0, 0,  0, 0, 0,
		0, 8, 7,  0, 0, 0,  0, 3, 1,

		0, 0, 3,  0, 1, 0,  0, 8, 0,
		9, 0, 0,  8, 6, 3,  0, 0, 5,
		0, 5, 0,  0, 9, 0,  6, 0, 0,
		
		1, 3, 0,  0, 0, 0,  2, 5, 0,
		0, 0, 0,  0, 0, 0,  0, 7, 4,
		0, 0, 5,  2, 0, 6,  3, 0, 0 
	}); 
	
	std::cout << "\n";
	if (sudoku.solve())
		std::cout << sudoku;
	else 
		std::cout << "\nNo solution found.\n";

	return 0;
}
