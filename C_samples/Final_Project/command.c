//
// Created by Mira Mastoras on 12/6/17.
//

#include "command.h"
#include "inputvalidation.h"
#include <stdio.h>



bool isValidCommand(char commandLetter,
                    const int numRows,
                    const int numCols,
                    writeCommands *writeCommandsP,
                    RowAndCol *eraseCommandsP,
                    RowAndCol *resizeCommandsP,
                    addOrDelete *addCommandsP,
                    addOrDelete *deleteCommandsP,
                    char* saveFileName,
                    char* loadFileName) {
  int numArgsRead;
  if (commandLetter == 'q') {
    if (isValidFormat(1, 1)){
      return true;
    }
    else {
      printf("Unrecognized command. Type h for help.\n");
      return false;
    }
  }
  else if (commandLetter == 'h') {
    if (isValidFormat(1,1)){
      return true;
    }
    else {
      printf("Unrecognized command. Type h for help.\n");
      return false;
    }
  }
  else if (commandLetter == 'w') {
    numArgsRead = scanf("%d %d %d %d", &(*writeCommandsP).startRow, &(*writeCommandsP).startCol, &(*writeCommandsP).endRow, &(*writeCommandsP).endCol);
    if (!isValidFormat(numArgsRead, 4)) {
      printf("Improper draw command.\n");
      return false;
    }
    else if (!(isWriteInRange(writeCommandsP, numRows,  numCols))) {
      printf("Improper draw command.\n");
      return false;
    }
    else {
      return true;
    }
  }
  else if (commandLetter == 'e') {
    numArgsRead = scanf("%d %d", &(*eraseCommandsP).Row, &(*eraseCommandsP).Col);
    if (!isValidFormat(numArgsRead, 2)) {
      printf("Improper erase command.\n");
      return false;
    }
    else if (!(isInRange((*eraseCommandsP).Row, (*eraseCommandsP).Col, numRows, numCols))) {
      printf("Improper erase command.\n");
      return false;
    } else {
      return true;
    }
  }
  else if (commandLetter == 'r') {
    numArgsRead = scanf("%d %d", &(*resizeCommandsP).Row, &(*resizeCommandsP).Col);
    if ((!isValidFormat(numArgsRead, 2))) {
      printf("Improper resize command.\n");
      return false;
    }
    else if(!(isResizeInRange(resizeCommandsP, numRows, numCols))) {
      printf("Improper resize command.\n");
      return false;
    } else {
      return true;
    }
  }
  else if (commandLetter == 'a') {
    numArgsRead = scanf(" %c %d", &(*addCommandsP).rowOrColChar, &(*addCommandsP).rowOrColInt);

    if ((!isValidFormat(numArgsRead, 2))) {
      printf("Improper add command.\n");
      return false;
    }

    else if (!(isAddInRange(addCommandsP, numRows, numCols))) {
      printf("Improper add command.\n");
      return false;
    }
    else {
      return true;
    }
  }
  else if (commandLetter == 'd') {
    numArgsRead = scanf(" %c %d", &(*deleteCommandsP).rowOrColChar, &(*deleteCommandsP).rowOrColInt);

    if ((!isValidFormat(numArgsRead, 2))) {
      printf("Improper delete command.\n");
      return false;
    }
    else if (!(isDeleteInRange(deleteCommandsP, numRows, numCols))) {
      printf("Improper delete command.\n");
      return false;
    }
    else {
      return true;
    }
  }
  else if (commandLetter == 's') {
    scanf(" %s", saveFileName);
    return true;
  }
  else if (commandLetter == 'l') {
    scanf(" %s", loadFileName);
    if (!(isLoadFileValid(loadFileName))){
      return false;
    } else {
      return true;
    }
  }
  else {
    printf("Unrecognized command. Type h for help.\n");
    isValidFormat(1, 1);
    return false;
  }
  return false;
}

void getCommand(Board* theBoard,
                writeCommands *writeCommandsP,
                RowAndCol *eraseCommandsP,
                RowAndCol *resizeCommandsP,
                addOrDelete *addCommandsP,
                addOrDelete *deleteCommandsP,
                char *saveFileName,
                char *loadFileName,
                char *commandLetter) {

  do {
    displayBoard((*theBoard).board, (*theBoard).numRows, (*theBoard).numCols);
    printf("Enter your command: \n");
    scanf(" %c", commandLetter);
  } while (!isValidCommand(*commandLetter, (*theBoard).numRows, (*theBoard).numCols, writeCommandsP, eraseCommandsP, resizeCommandsP, addCommandsP, deleteCommandsP, saveFileName, loadFileName));
}
