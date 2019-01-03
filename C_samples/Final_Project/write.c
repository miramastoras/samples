//
// Created by Mira Mastoras on 12/8/17.
//

#include "write.h"
#include <stdlib.h>
#include <stdio.h>


// draw left to right horizontal

void drawLToR_Horizontal(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int startCol = writeCommandsP->startCol;
  int endCol = writeCommandsP->endCol;

  for(int c = startCol; c <= endCol; c++){
    if (theBoard->board[startRow][c] == '*' || theBoard->board[startRow][c] == '-') {
      theBoard->board[startRow][c] = '-';
    }
    else{
      theBoard->board[startRow][c] = '+';
    }
  }
}

// draw right to left horizontal

void drawRToL_Horizontal(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int startCol = writeCommandsP->startCol;
  int endCol = writeCommandsP->endCol;

  for(int c = startCol; c >= endCol; c--){
    if (theBoard->board[startRow][c] == '*' || theBoard->board[startRow][c] == '-') {
      theBoard->board[startRow][c] = '-';
    }
    else{
      theBoard->board[startRow][c] = '+';
    }
  }
}

// draw top down vertical
void drawTopDownVertical(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int endRow = (theBoard->numRows - 1) - (writeCommandsP->endRow);
  int startCol = writeCommandsP->startCol;

  for(int r = startRow; r <= endRow; r++){
    if (theBoard->board[r][startCol] == '*' || theBoard->board[r][startCol] == '|') {
      theBoard->board[r][startCol] = '|';
    }
    else{
      theBoard->board[r][startCol] = '+';
    }
  }
}

// draw bottom up vertical

void drawBottomUpVertical(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int endRow = (theBoard->numRows - 1) - (writeCommandsP->endRow);
  int startCol = writeCommandsP->startCol;

  for(int r = startRow; r >= endRow; r--){
    if (theBoard->board[r][startCol] == '*' || theBoard->board[r][startCol] == '|') {
      theBoard->board[r][startCol] = '|';
    }
    else{
      theBoard->board[r][startCol] = '+';
    }
  }
}

// draw left to right right diagonal
void drawLToR_RightDiag(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int endRow = (theBoard->numRows - 1) - (writeCommandsP->endRow);
  int startCol = writeCommandsP->startCol;
  int endCol = writeCommandsP->endCol;

  int r = startRow;
  int c = startCol;
  while (r <= endRow && c <= endCol){
    if (theBoard->board[r][c] == '\\' || theBoard->board[r][c] == '*'){
      theBoard->board[r][c] = '\\';
      r++;
      c++;
    }
    else {
      theBoard->board[r][c] = '+';
      r++;
      c++;
    }
  }
}

// draw right to left right diagonal

void drawRToL_RightDiag(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int endRow = (theBoard->numRows - 1) - (writeCommandsP->endRow);
  int startCol = writeCommandsP->startCol;
  int endCol = writeCommandsP->endCol;

  int r = startRow;
  int c = startCol;
  while (r >= endRow && c >= endCol){
    if (theBoard->board[r][c] == '\\' || theBoard->board[r][c] == '*'){
      theBoard->board[r][c] = '\\';
      r--;
      c--;
    }
    else {
      theBoard->board[r][c] = '+';
      r--;
      c--;
    }
  }
}

// draw left to right left diagonal

void drawLToR_LeftDiag(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int endRow = (theBoard->numRows - 1) - (writeCommandsP->endRow);
  int startCol = writeCommandsP->startCol;
  int endCol = writeCommandsP->endCol;

  int r = startRow;
  int c = startCol;
  while (r >= endRow && c <= endCol){
    if (theBoard->board[r][c] == '/' || theBoard->board[r][c] == '*'){
      theBoard->board[r][c] = '/';
      r--;
      c++;
    }
    else {
      theBoard->board[r][c] = '+';
      r--;
      c++;
    }
  }
}
// draw right to left left diagonal

void drawRToL_LeftDiag(Board *theBoard, writeCommands *writeCommandsP) {
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int endRow = (theBoard->numRows - 1) - (writeCommandsP->endRow);
  int startCol = writeCommandsP->startCol;
  int endCol = writeCommandsP->endCol;

  int r = startRow;
  int c = startCol;
  while (r <= endRow && c >= endCol){
    if (theBoard->board[r][c] == '/' || theBoard->board[r][c] == '*'){
      theBoard->board[r][c] = '/';
      r++;
      c--;
    }
    else {
      theBoard->board[r][c] = '+';
      r++;
      c--;
    }
  }
}

// decides which direction to draw in or if valid

void commandWrite(Board* theBoard, writeCommands* writeCommandsP){
  // here I had to correct for the opposite orientation of the user commands to the actual indexing of the board
  // the columns are correctly oriented but not the rows
  int startRow = (theBoard->numRows - 1) - (writeCommandsP->startRow);
  int endRow = (theBoard->numRows - 1) - (writeCommandsP->endRow);


  if (startRow == endRow){
    if (writeCommandsP->startCol < writeCommandsP->endCol) {
      drawLToR_Horizontal(theBoard, writeCommandsP);
    }
    else{
      drawRToL_Horizontal(theBoard, writeCommandsP);

    }
  }
  else if (writeCommandsP->startCol == writeCommandsP->endCol){
    if (startRow < endRow){
      drawTopDownVertical(theBoard, writeCommandsP);
    }
    else{
      drawBottomUpVertical(theBoard, writeCommandsP);
    }
  }
  else if (abs(startRow - endRow) == abs(writeCommandsP-> startCol - writeCommandsP->endCol)){
    if ((startRow < endRow) && (writeCommandsP->startCol < writeCommandsP->endCol)) {
      drawLToR_RightDiag(theBoard, writeCommandsP);
    }
    else if ((startRow > endRow) && (writeCommandsP->startCol > writeCommandsP->endCol)){
      drawRToL_RightDiag(theBoard, writeCommandsP);
    }
    else if ((startRow > endRow) && (writeCommandsP->startCol < writeCommandsP->endCol)){
      drawLToR_LeftDiag(theBoard, writeCommandsP);
    }
    else if ((startRow < endRow) && (writeCommandsP->startCol > writeCommandsP->endCol)){
      drawRToL_LeftDiag(theBoard, writeCommandsP);
    }
    else{
    }
  }
  else {
    printf("Cannot draw the line as it is not straight.\n");
  }

}
