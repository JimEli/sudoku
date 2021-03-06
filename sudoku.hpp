// Basic sudoku solver.
// 7/15/2018 JME.

#include <iostream>
#include <array>

class Sudoku
{
public:
	// Ctor.
	Sudoku(std::array<unsigned, 81> p) : puzzle(p) { }

	// Solver calls private recursive solver function.
	bool solve() { return solve(puzzle, 0, 0); };

	// print puzzle.
	friend std::ostream& operator<< (std::ostream& os, const Sudoku& s)
	{
		for (unsigned i = 1; i < 82; i++)
			os << s.puzzle[i - 1] << ((!(i % 9)) ? "\n" : " ");
		return os;
	}

private:
	std::array<unsigned, 81> puzzle;

	// Check if value is valid for the square.
	bool isAvailable(std::array<unsigned, 81> puzzle, int row, int column, int n)
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
	bool solve(std::array<unsigned, 81> &puzzle, int row, int column)
	{
		// Completed all squares?
		if (row < 9 && column < 9)
		{
			// Square already filled?
			if (puzzle[9 * row + column])
			{
				// Check all columns and rows.
				if ((column + 1) < 9)
					return solve(puzzle, row, column + 1);
				else if ((row + 1) < 9)
					return solve(puzzle, row + 1, 0);
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
							if (solve(puzzle, row, column + 1))
								return true;
							else
								// Failure, so backtrack.
								puzzle[9 * row + column] = 0;
						else if ((row + 1) < 9)
							// Attempt to complete all rows.
							if (solve(puzzle, row + 1, 0))
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
