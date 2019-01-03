//
// Created by Mira Mastoras on 12/6/17.
//

#include <stdbool.h>
#include "board.h"



#ifndef FINALPROJECT_COMMAND_H
#define FINALPROJECT_COMMAND_H
typedef struct addOrDelete_struct{
  char rowOrColChar;
  int rowOrColInt;
}addOrDelete;

typedef struct writeCommands_struct{
  int startRow;
  int startCol;
  int endRow;
  int endCol;
}writeCommands;

typedef struct rowAndCol_struct{
  int Row;
  int Col;
}RowAndCol;


bool isValidCommand(char commandLetter, const int numRows, const int numCols, writeCommands* writeCommandsP,
                    RowAndCol* eraseCommandsP, RowAndCol* resizeCommandsP,addOrDelete* addCommandsP, addOrDelete* deleteCommandsP, char* saveFileName, char* loadFileName);


void getCommand(Board* theBoard, writeCommands *writeCommandsP,
                RowAndCol *eraseCommandsP,
                RowAndCol *resizeCommandsP,
                addOrDelete *addCommandsP,
                addOrDelete *deleteCommandsP,
                char* saveFileName,
                char* loadFileName,char* commandLetter);

#endif //FINALPROJECT_COMMAND_H
