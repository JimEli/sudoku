#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

class Sudoku
{
public:
	Sudoku(std::initializer_list<unsigned> digits) : puzzle(digits) { }

	void setPuzzle(std::vector<unsigned> digits)
	{
		if (digits.size() != 81) return;
		for (int i = 0; i < 81; i++) puzzle[i] = digits[i];
	};

	std::vector<unsigned> getPuzzle() const { return puzzle; };

	bool solve() { return solveSudoku(puzzle, 0, 0); };

	friend std::ostream& operator<< (std::ostream& os, const Sudoku& s)
	{
		for (unsigned i = 1; i < 82; i++)
			os << s.puzzle[i - 1] << ((!(i % 9)) ? "\n" : " ");
		return os;
	}

private:
	std::vector<unsigned> puzzle;

	// Check if value is valid for the square.
	bool isAvailable(std::vector<unsigned> puzzle, int row, int column, int n)
	{
		// Calculate top right corner of sub-square. 
		int rowStart = (row / 3) * 3;
		int colStart = (column / 3) * 3;

		for (int i = 0; i < 9; ++i)
		{
			// Is same value in the row?
			if (puzzle[9 * row + i] == n)
				return false;
			// Is same value in the column?
			if (puzzle[9 * i + column] == n)
				return false;
			// Is same value inside 3x3 sub-square?
			if (puzzle[(9 * (rowStart + (i % 3))) + colStart + (i / 3)] == n)
				return false;
		}
		return true;
	}

	// Recursively attempt to fill all squares.
	bool solveSudoku(std::vector<unsigned> &puzzle, int row, int column)
	{
		if (puzzle.size() != 81)
			return false;

		// Completed all squares?
		if (row < 9 && column < 9)
		{
			// Square already filled?
			if (puzzle[9 * row + column])
			{
				// Check all columns and rows.
				if ((column + 1) < 9)
					return solveSudoku(puzzle, row, column + 1);
				else if ((row + 1) < 9)
					return solveSudoku(puzzle, row + 1, 0);
				else
					return true;
			}
			else
			{
				for (int digit = 1; digit < 10; ++digit)
				{
					// Try (all) valid numbers.
					if (isAvailable(puzzle, row, column, digit))
					{
						puzzle[9 * row + column] = digit;

						if ((column + 1) < 9)
							// Attempt to complete all columns.
							if (solveSudoku(puzzle, row, column + 1))
								return true;
							else
								// Failure, so backtrack.
								puzzle[9 * row + column] = 0;
						else if ((row + 1) < 9)
							// Attempt to complete all rows.
							if (solveSudoku(puzzle, row + 1, 0))
								return true;
							else
								// Failure, so backtrack.
								puzzle[9 * row + column] = 0;
						else
							return true;
					}
				}
			}
			// Failed.
			return false;
		}
		else
			// Should never reach here.
			return true;
	}
};
