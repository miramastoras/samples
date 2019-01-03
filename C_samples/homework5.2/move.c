//
// Created by Mira Mastoras on 11/15/17.
//

#include "move.h"
#include <stdio.h>

int getColPicked(const int numCols, char** board) {
  int colPicked;
  do {
    printf("Enter a column between 0 and %d to play in: ", numCols - 1);
    scanf("%d", &colPicked);
  } while (!((colPicked >= 0) && (colPicked < numCols) && (board[0][colPicked] == '*')));

  return colPicked;
}

void makeMove(char** board, const int colPicked, const int numRows, const char pieces) {
  for (int row = (numRows - 1); row >= 0; --row) {
    if (board[row][colPicked] == '*'){
      board[row][colPicked] = pieces;
      return;
    }
  }

}


