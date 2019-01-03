//
// Created by Mira Mastoras on 12/8/17.
//
#include <stdbool.h>
#include "command.h"
#ifndef FINALPROJECT_INPUTVALIDATION_H
#define FINALPROJECT_INPUTVALIDATION_H


bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool isLoadFileValid( char* loadFileName);
bool isAddInRange(addOrDelete* addCommandsP, const int numRows, const int numCols);
bool isDeleteInRange(addOrDelete* deleteCommandsP, const int numRows, const int numCols);
bool isWriteInRange(writeCommands* writeCommandsP, const int numRows, const int numCols);
bool isResizeInRange(RowAndCol* resizeCommandsP, const int numRows, const int numCols);
bool isInRange(int userRow, int userCol, const int numRows, const int numCols);

#endif //FINALPROJECT_INPUTVALIDATION_H
