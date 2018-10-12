/*
 * C++ Program to Solve Sudoku Problem using BackTracking
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

#define UNASSIGNED 0 // Convenience value for unassigned cell initialization
#define N 9

class SudokuBoard {
public:
  SudokuBoard(const std::vector<std::vector<int>>& initial_grid);

  void setCell(int row, int col, int num);

  bool FindUnassignedLocation(int &row, int &col);

  bool isSafe(int row, int col, int num);

  /* print grid  */
  void printGrid();

  const std::vector<std::vector<int>>& getBoard();

  bool ValidateBoard();
  
  //My counting method
  //int Count(int add);

private:

  std::vector<std::vector<int>> grid;

  /* Find if a number has been used in the row. */
  bool UsedInRow(int row, int num);

  /* Find if a number has been used in a column. */
  bool UsedInCol(int col, int num);

  /* Finds if a number has been used in a box. */
  bool UsedInBox(int boxStartRow, int boxStartCol, int num);

  bool ValidBoard();

};
 
 
/* 
  assign values to all unassigned locations for Sudoku solution  
 */
bool SolveSudoku(SudokuBoard* board, int row=0, int col=0);

#endif