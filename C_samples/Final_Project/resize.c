//
// Created by Mira Mastoras on 12/12/17.
//

#include "resize.h"
#include <stdio.h>
#include <stdlib.h>
// adds one new row, shifts everything else down by one
void addNewRowAt(int position, Board *theBoard) {

  int realPosition = ((theBoard->numRows)) - (position);

  /**if(position == 0 ){
    realPosition = theBoard->numRows;
  }
  else if(position == theBoard->numRows){
    realPosition = 0;
  }
  else {
    realPosition = ((theBoard->numRows)) - (position);
  }**/
  // make space for the row pointer
  theBoard->board = (char** ) realloc(theBoard->board, (theBoard->numRows + 1) * sizeof(char*));
  // make space for the elements in the new row

  for (int r = theBoard->numRows; r > realPosition ; --r) {
    theBoard->board[r] = theBoard->board[r-1];

  }
  theBoard->board[realPosition] = (char*) malloc(theBoard->numCols * sizeof(char));
  for (int col = 0; col < theBoard->numCols; col++) {
    (*theBoard).board[realPosition][col] = '*';
  }
  (theBoard->numRows)++;
}

// delete a row
void deleteARowAt(int RowPosition,Board* theBoard){
  // overwrite deleted row
  free(theBoard->board[RowPosition]);

  for(int r = RowPosition; r < theBoard->numRows - 1; r++){
    theBoard->board[r] = theBoard->board[r+1];
  }
  theBoard->board = (char** ) realloc(theBoard->board, (theBoard->numRows - 1) * sizeof(char*));
  (theBoard->numRows)--;


  /*for (int r = RowPosition; r > 0; r--){
    for(int c = 0; c < theBoard-> numCols; c++){
      (*theBoard).board[r][c] = (*theBoard).board[r-1][c];
    }
  }
  // shift all down
 for(int row = 0; row < theBoard->numRows - 1; row ++){
    for(int col = 0; col < theBoard-> numCols; col++){
      (*theBoard).board[row ][col] = (*theBoard).board[row + 1][col];
    }
  }*/
}
// add new column
void addNewColAt(int newColPosition,Board* theBoard){

  for (int r = 0; r < theBoard->numRows ; r++) {
    (theBoard->board)[r] = (char *) realloc(theBoard->board[r], (theBoard->numCols + 1) * sizeof(char));

    for(int c = theBoard->numCols; c > newColPosition ; c--){
      (*theBoard).board[r][c] = (*theBoard).board[r][c-1];
    }
    (*theBoard).board[r][newColPosition] = '*';
  }
  (theBoard->numCols) ++;
}

// delete a column
void deleteAColAt(int ColPosition, Board* theBoard){
  for (int r = 0; r < theBoard->numRows ; r++) {
    for (int c = ColPosition; c < theBoard->numCols - 1; c++){
      (*theBoard).board[r][c] = (*theBoard).board[r][c + 1];
    }
    (theBoard->board)[r] = (char *) realloc(theBoard->board[r], (theBoard->numCols - 1) * sizeof(char));
  }
  (theBoard->numCols) --;
}


void commandResize(Board *theBoard, RowAndCol *resizeCommandsP) {
  int newRowSize = (resizeCommandsP->Row);
  int newColSize = (resizeCommandsP->Col);
  int curRowSize = theBoard->numRows;
  int curColSize = theBoard->numCols;

  if (newRowSize < 1 || resizeCommandsP->Col < 1) {
    printf("Improper resize command.\n");
  }
  // resize rows
  if (newRowSize > curRowSize){
    for (int c = curRowSize ; c < newRowSize; c++){
      addNewRowAt(c, theBoard);
    }
  }
  else if (newRowSize < curRowSize){
    for (int c = 0; c < curRowSize - newRowSize; c++){
      deleteARowAt(0, theBoard);
    }
  }


  // resize columns
  if (newColSize > curColSize){
    for(int c = 0; c < newColSize - curColSize; c++){
      addNewColAt(theBoard->numCols, theBoard);
    }
  }
  else if (newColSize < curColSize){
    for (int c = 0; c < curColSize - newColSize; c++){
      deleteAColAt(theBoard->numCols - 1, theBoard);
    }
  }
}

void commandAdd(Board *theBoard, addOrDelete *addCommandsP) {


  if (addCommandsP->rowOrColChar == 'c' || addCommandsP->rowOrColChar == 'C'){
    addNewColAt(addCommandsP->rowOrColInt, theBoard);
  }
  else {
    addNewRowAt(addCommandsP->rowOrColInt, theBoard);
  }
}


void commandDelete(Board *theBoard, addOrDelete *deleteCommandsP) {
  int newRow = ((theBoard->numRows) - 1) - (deleteCommandsP->rowOrColInt);
  if (deleteCommandsP->rowOrColChar == 'c' || deleteCommandsP->rowOrColChar == 'C'){
    deleteAColAt(deleteCommandsP->rowOrColInt, theBoard);
  }
  else{
    deleteARowAt(newRow, theBoard);
  }
}


