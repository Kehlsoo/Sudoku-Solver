/*
 * C++ Program to Solve Sudoku Problem using BackTracking
 */

#include "sudoku.h"

/* Initialize the data structure to hold the grid. */
SudokuBoard::SudokuBoard(const std::vector<std::vector<int>>& initial_grid) {
  grid = initial_grid;
};

/* Set the value of a cell. */
void SudokuBoard::setCell(int row, int col, int num) {
  grid[row][col] = num;
};

/* Find a valid location to place a number. */
bool SudokuBoard::FindUnassignedLocation(int &row, int &col) {
  for (row = 0; row < N; row++) {
    for (col = 0; col < N; col++) {
      if (grid[row][col] == 0){
        return true;
      }
    }
  }
  return false;

};

/* Determine if a move is safe. */
bool SudokuBoard::isSafe(int row, int col, int num) {
  if((UsedInRow(row, num) == false) && (UsedInCol(col, num) == false) && (UsedInBox(row - row % 3, col - col % 3, num) == false)){
    return true;
  }
  return false;
};

/* Print a grid out to the screen.  */
void SudokuBoard::printGrid() {
  for (int row = 0; row < N; row++)
  {
    for (int col = 0; col < N; col++)
      std::cout << grid[row][col] << "  ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
};

/* Validate Board */
bool SudokuBoard::ValidateBoard() {
  return ValidBoard();
}

/* Return a const reference to the sudoku board. */
const std::vector<std::vector<int>>& SudokuBoard::getBoard() {
  return grid;
}

/* Find if a number has been used in the row. */
bool SudokuBoard::UsedInRow(int row, int num) {
 for (int col = 0; col < N; col++) {
  if(grid[row][col] == num){
   return true;
 }
}
return false;
};

/* Find if a number has been used in a column. */
bool SudokuBoard::UsedInCol(int col, int num) {
 for (int row = 0; row < N; row++) {
  if(grid[row][col] == num){

    return true;
  }
}
return false;
};

/* Finds if a number has been used in a box. */
bool SudokuBoard::UsedInBox(int boxStartRow, int boxStartCol, int num) {
  for (int row = 0; row < 3; row++){
    for (int col = 0; col < 3; col++){
      if(grid[row + boxStartRow][col + boxStartCol] == num){
       return true;

     }
   }
 }
 return false;
};

/* Find if the board state is valid. */
bool SudokuBoard::ValidBoard() {
  for (int row = 0; row < N; row++){
    for (int col = 0; col < N; col++){
      int num = grid[row][col];

      if ( (num < 0) || (num > 9)){
        return false;
      }

      if((UsedInRow(row, num) == true) || (UsedInCol(col, num) == true) || (UsedInBox(row - row % 3, col - col % 3, num) == true)){
        return false;
      }
    }
  }
  return true;
};

// int SudokuBoard::Count(int add){
//   int count = count + add;
//   return count;

// };


/* 
  The main driving algorithm to solve a sudoku board using
  backtracking.  You *may* need to modify this function 
  to keep track of how many steps it took to solve.

  Algorithm:
    - Find an unassigned location.
    - Determine if a move is safe.
    - If so:
    -   Proceed along that path filling in subsequent cells.
    - Else:
    -   Reset the cell and try another number in that cell.
    - Return False if the board cannot be solved.
 */
bool SolveSudoku(SudokuBoard* board, int row, int col) {

  //Finding an unassigned place, it there aren't any, the it is solved
  if (!board->FindUnassignedLocation(row,col)) {
    return true;
  }

  auto grid = board->getBoard();

  //if location is zero will go through 1-9
  if (grid[row][col] == 0){
   for (int i = 1; i <= 9; i++){

    //board->Count(1);

    //if the value is safe will set value 
    if (board->isSafe(row, col, i) == true){
      board->setCell(row, col, i);

      //board is solved if returns true
      if (SolveSudoku(board, row, col) == true){
        //std::cout << board->Count(0)  << std::endl;
        return true;

      //Returns location back to zero if value doesn't work
      } else {
        board->setCell(row, col, 0);
      }
    }
  } 
}
return false;
}

#ifndef CATCH_TEST

/* Main */
int main()
{
  std::vector<std::vector<int>> starting_grid {
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

    // An example of an unsolvable starting grid solution.
  std::vector<std::vector<int>> unsolvable_starting_grid {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {6, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
  };

  std::vector<std::vector<int>> solvable_2 {
    {1, 7, 5, 2, 9, 4, 8, 3, 6},
    {0, 2, 3, 0, 8, 0, 0, 4, 0},
    {8, 0, 0, 0, 6, 3, 2, 0, 1},
    {5, 0, 0, 7, 3, 2, 4, 0, 0},
    {0, 4, 0, 8, 5, 6, 0, 2, 0},
    {0, 8, 0, 9, 4, 1, 7, 0, 3},
    {9, 3, 8, 4, 2, 5, 0, 0, 7},
    {0, 6, 0, 0, 7, 0, 5, 8, 0},
    {7, 5, 0, 0, 1, 8, 3, 9, 0}
  };


   // The process of initializing, printing, testing viability,
    //and solving a board.
  auto board = new SudokuBoard(starting_grid);


  SolveSudoku(board);
  //std::cout << board->Count(0);
};

#endif