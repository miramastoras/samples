//
// Created by Mira Mastoras on 12/5/17.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

typedef struct Board_struct{
  int numRows;
  int numCols;
  char** board;
}Board;

char** createBoard(const int num_rows, const int num_cols, const char blank_space);
void displayBoard(char** board, const int num_rows, const int num_cols);
void cleanUp(char*** board, const int num_rows, const int num_cols);
#endif //FINALPROJECT_BOARD_H
