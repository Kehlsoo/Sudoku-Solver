/*
	Homework #5:

	Write sudoko for backtracking.  

	Commands to run:
	Mac OSX: Modify the makefile to include -stdlib=libc++
	EOS: run 'make' from the command line in the root of the project.

	Concepts Covered:
	Backtracking
	Pointers
	Includes

*/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "sudoku.h"
#include <vector>

std::vector<std::vector<int>> solvable_1 {
	{3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
};

std::vector<std::vector<int>> solvable_1_solved {
	{ 3, 1, 6, 5, 7, 8, 4, 9, 2 }, 
	{ 5, 2, 9, 1, 3, 4, 7, 6, 8 }, 
	{ 4, 8, 7, 6, 2, 9, 5, 3, 1 }, 
	{ 2, 6, 3, 4, 1, 5, 9, 8, 7 }, 
	{ 9, 7, 4, 8, 6, 3, 1, 2, 5 }, 
	{ 8, 5, 1, 7, 9, 2, 6, 4, 3 }, 
	{ 1, 3, 8, 9, 4, 7, 2, 5, 6 }, 
	{ 6, 9, 2, 3, 5, 1, 8, 7, 4 }, 
	{ 7, 4, 5, 2, 8, 6, 3, 1, 9 }
};

//basic solving test
TEST_CASE( " Basic Test Sudoku solver with backtracking", "[valid]") {
	auto board = new SudokuBoard(solvable_1);
	
	bool solved = SolveSudoku(board);
	REQUIRE(solved == true);
	REQUIRE(solvable_1_solved == board->getBoard());
}

//board with repeated values in the column
std::vector<std::vector<int>> invalid_1 {
	{3, 0, 6, 5, 0, 8, 4, 0, 0},
    {3, 2, 0, 0, 0, 0, 0, 0, 0},
    {3, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 7, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
};

//board with repeated values in the box
std::vector<std::vector<int>> invalid_2 {
	{3, 0, 6, 5, 0, 8, 4, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 7, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 3, 3, 3},
    {0, 0, 0, 0, 0, 0, 3, 3, 3},
    {0, 0, 5, 2, 0, 6, 3, 3, 3}
};

//board with repeated values in the row
std::vector<std::vector<int>> invalid_3 {
	{3, 0, 6, 5, 5, 5, 5, 5, 0},
    {0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 7, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 3, 3, 3},
    {0, 0, 0, 0, 0, 0, 3, 3, 3},
    {0, 0, 5, 2, 0, 6, 3, 3, 3}
};

//board with invalid numbers
std::vector<std::vector<int>> invalid_4 {
	{0, 0, 6, 5, 0, 8, 4, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 33, 0, 0, 0, 3, 1},
    {0, 0, 7, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 50, 3, 3},
    {0, 0, 0, 0, 0, 0, 3, 3, 3},
    {0, 0, 5, 2, 0, 6, 3, 3, 3}
};


//testing for valid boards
TEST_CASE( "Checking for valid tables", "[valid]") {
	auto board = new SudokuBoard(invalid_1);
	auto board_2 = new SudokuBoard(invalid_2);
	auto board_3 = new SudokuBoard(invalid_3);
	auto board_4 = new SudokuBoard(invalid_4);

	bool validate = board->ValidateBoard();
	REQUIRE(validate == false);

	validate = board_2->ValidateBoard();
	REQUIRE(validate == false);

	validate = board_3->ValidateBoard();
	REQUIRE(validate == false);

	validate = board_4->ValidateBoard();
	REQUIRE(validate == false);


}

std::vector<std::vector<int>> solvable_2 {
	{0, 7, 5, 0, 9, 0, 0, 0, 6},
    {0, 2, 3, 0, 8, 0, 0, 4, 0},
    {8, 0, 0, 0, 0, 3, 0, 0, 1},
    {5, 0, 0, 7, 0, 2, 0, 0, 0},
    {0, 4, 0, 8, 0, 6, 0, 2, 0},
    {0, 0, 0, 9, 0, 1, 0, 0, 3},
    {9, 0, 0, 4, 0, 0, 0, 0, 7},
    {0, 6, 0, 0, 7, 0, 5, 8, 0},
    {7, 0, 0, 0, 1, 0, 3, 9, 0}
};

std::vector<std::vector<int>> solvable_2_solved {
	{1, 7, 5, 2, 9, 4, 8, 3, 6},
    {6, 2, 3, 1, 8, 7, 9, 4, 5},
    {8, 9, 4, 5, 6, 3, 2, 7, 1},
    {5, 1, 9, 7, 3, 2, 4, 6, 8},
    {3, 4, 7, 8, 5, 6, 1, 2, 9},
    {2, 8, 6, 9, 4, 1, 7, 5, 3},
    {9, 3, 8, 4, 2, 5, 6, 1, 7},
    {4, 6, 1, 3, 7, 9, 5, 8, 2},
    {7, 5, 2, 6, 1, 8, 3, 9, 4}
};

std::vector<std::vector<int>> solvable_3 {
	{0, 7, 5, 0, 9, 0, 0, 0, 6},
    {0, 2, 0, 0, 8, 0, 0, 4, 0},
    {8, 0, 0, 0, 0, 3, 0, 0, 1},
    {5, 0, 0, 7, 0, 2, 0, 0, 0},
    {0, 4, 0, 8, 0, 6, 0, 2, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 3},
    {9, 0, 0, 4, 0, 0, 0, 0, 7},
    {0, 6, 0, 0, 7, 0, 5, 8, 0},
    {7, 0, 0, 0, 1, 0, 3, 0, 0}
};

//Solving complicated boards
TEST_CASE( "Solving more complicated boards", "[valid]") {
	auto board = new SudokuBoard(solvable_2);
	auto board_2 = new SudokuBoard(solvable_3);
	

	bool solved = SolveSudoku(board);
	REQUIRE(solved == true);
	REQUIRE(solvable_2_solved == board->getBoard());

	//Same board is tested, just altered with less values
	solved = SolveSudoku(board_2);
	REQUIRE(solved == true);
	REQUIRE(solvable_2_solved == board_2->getBoard());
}