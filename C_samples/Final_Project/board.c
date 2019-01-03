//
// Created by Mira Mastoras on 12/5/17.
//

#include "board.h"
#include <stdlib.h>
#include <stdio.h>


char** createBoard(const int numRows, const int numCols, const char blank_space) {
  char** board = (char** ) malloc(numRows * sizeof(char* ));
  for (int row = 0; row < numRows; ++row) {
    board[row] = (char* ) malloc(numCols * sizeof(char));
    for (int col = 0; col < numCols; ++col) {
      board[row][col] = blank_space;
    }
  }
  return board;
}

void displayBoard(char** board, int numRows, int numCols) { //prints out created board
  int i, j;

  for (i = 0; i < numRows; ++i) {
    if (numRows - i - 1 < 10){
      printf(" ");
    }
      printf("%d ", numRows - i - 1);
    for (j = 0; j < numCols; ++j) {
      printf(" %c ", board[i][j]);
    }
    printf("\n");
  }

  printf("   ");
  for (j = 0; j < numCols; ++j) {
    if (j < 10){
     printf(" ");
    }
    printf("%d ", j);
  }
  printf("\n");
}

void cleanUp(char*** board, const int numRows, const int numCols) {
  for (int row = 0; row < numRows; ++row) {
    free((*board)[row]);
  }
  free(*board);
  *board = NULL;
}
//