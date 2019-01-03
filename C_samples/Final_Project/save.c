//
// Created by Mira Mastoras on 12/14/17.
//

#include "save.h"
#include <stdio.h>
#include <stdlib.h>


void commandSave(Board* theBoard, char* saveFileName) {
  FILE* file;
  file = fopen(saveFileName, "w");

  if(file == NULL) {
    printf("Failed to open file: %s\n", saveFileName);
    return;
  }

  int numRows = theBoard->numRows;
  int numCols = theBoard->numCols;


  fprintf(file, "%d %d\n", numRows, numCols);
  int i, j;

  for (i = 0; i < numRows; ++i) {
    for (j = 0; j < numCols; ++j) {
      fprintf(file, "%c ", theBoard->board[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);

}