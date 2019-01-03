//
// Created by Mira Mastoras on 12/8/17.
//

#include "help.h"
#include <stdio.h>

void print_help(){

  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}


void commandErase(Board* theBoard, RowAndCol* eraseCommandsP) {
  // here I had to correct for the opposite orientation of the user commands to the actual indexing of the board
  // the columns are correctly oriented but not the rows

  int row = (theBoard->numRows - 1) - (eraseCommandsP->Row);
  int col = eraseCommandsP->Col;

  theBoard->board[row][col] = '*';

}