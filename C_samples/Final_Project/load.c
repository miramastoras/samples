//
// Created by Mira Mastoras on 12/14/17.
//

#include "load.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

void commandLoad(Board* theBoard, char* loadFileName) {
  FILE* file;
  file = fopen(loadFileName, "r");

  if(file == NULL) {
    printf("Failed to open file: %s\n", loadFileName);
    return;
  }

  RowAndCol loadCommandsP;
  int numRows;
  int numCols;
  fscanf(file, "%d", &numRows);
  fscanf(file, "%d", &numCols);
  loadCommandsP.Row = numRows;
  loadCommandsP.Col = numCols;
  // printf("num rows: %d\n", loadCommandsP.Row);
  // printf("num cols: %d\n", loadCommandsP.Col);

  commandResize(theBoard, &loadCommandsP);


  for(int row = 0; row < numRows; ++ row) {
    for(int col = 0; col < numCols; ++ col) {
      fscanf(file, " %c", &theBoard->board[row][col]);
    }
  }

  fclose(file);

}