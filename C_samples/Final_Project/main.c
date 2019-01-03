#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "board.h"
#include "command.h"
#include "help.h"
#include "write.h"
#include "resize.h"
#include "save.h"
#include "load.h"

bool isFormatValid() {
  bool formatIsGood = true;
  char character;
  do {
    scanf("%c", &character);
    if (!isspace(character)) {
      formatIsGood = false;
    } //formatIsGood = formatIsGood && isspace(character); //formatIsGood = isspace(character) ? formatIsGood : false;
  }while(character != '\n');
  return formatIsGood;
}


void playPaint(int numRows, int numCols) {
  const char blankSpace = '*';
  Board theBoard;

  theBoard.numRows = numRows;
  theBoard.numCols = numCols;
  theBoard.board = createBoard(numRows, numCols, blankSpace);

  char commandLetter ='\0';
  writeCommands writeCommandsP;
  RowAndCol eraseCommandsP;
  RowAndCol resizeCommandsP;
  addOrDelete addCommandsP;
  addOrDelete deleteCommandsP;
  char saveFileName[200];
  char loadFileName[200];

  do {
    getCommand(&theBoard, &writeCommandsP, &eraseCommandsP, &resizeCommandsP, &addCommandsP, &deleteCommandsP, saveFileName, loadFileName, &commandLetter);
    commandLetter = tolower(commandLetter);
    if (commandLetter == 'q') {
      //commandQuit();
    } else if (commandLetter == 'h') {
      print_help();

    } else if (commandLetter == 'w') {
      commandWrite(&theBoard, &writeCommandsP);

    } else if (commandLetter == 'e') {
      commandErase(&theBoard, &eraseCommandsP);

    } else if (commandLetter == 'r') {
      commandResize(&theBoard, &resizeCommandsP);

    } else if (commandLetter == 'a') {
      commandAdd(&theBoard, &addCommandsP);

    } else if (commandLetter == 'd') {
      commandDelete(&theBoard, &deleteCommandsP);

    } else if (commandLetter == 's') {
      commandSave(&theBoard, saveFileName);

    } else if (commandLetter == 'l') {
      commandLoad(&theBoard, loadFileName);
    }
  } while (commandLetter != 'q');

  cleanUp(&theBoard.board, theBoard.numRows, theBoard.numCols);
}

void checkCommandLineArgs(int numArgsEntered, int numArgsNeeded, char** argv, int* numRows, int* numCols) {
  int numArgsScannedInR;
  int numArgsScannedInC;


  if (numArgsEntered == numArgsNeeded) { // what condition would we use to check if user entered word
    numArgsScannedInR = (sscanf(argv[1], "%d", numRows));
    numArgsScannedInC = (sscanf(argv[2], "%d", numCols));

    if ( numArgsScannedInR == 1 && numArgsScannedInC == 1) {
      if (*numRows > 0 && *numCols > 0) {
        return;
      }
      else {
        if ((*numRows) < 1) {
          printf("The number of rows is less than 1.\nMaking default board of 10 X 10.\n");
        }
        else if ((*numCols) < 1) {
          printf("The number of columns is less than 1.\nMaking default board of 10 X 10.\n");
        }
        *numRows = 10;
        *numCols = 10;
      }
    }
    else{
      if (numArgsScannedInR != 1 ){
        printf("The number of rows is not an integer.\nMaking default board of 10 X 10.\n");
      }
      if (numArgsScannedInC != 1) {
        printf("The number of columns is not an integer.\nMaking default board of 10 X 10.\n");
      }
      *numRows = 10;
      *numCols = 10;
    }
  }
  else {
      if (numArgsEntered == 1){
        *numRows = 10;
        *numCols = 10;
      }
      else {
        printf("Wrong number of command line arguements entered.\nUsage: ./paint.out [num_rows num_cols]\nMaking default board of 10 X 10.\n");
        *numRows = 10;
        *numCols = 10;
      }
    }
  }
 // argc gives # args, argv gives the args as strings use atoi for #args
 int main(int argc, char** argv) {
   int numRows;
   int numCols;

   const int numArgs = argc;
   const int NUM_ARGS_NEEDED = 3;

   checkCommandLineArgs(numArgs, NUM_ARGS_NEEDED, argv, &numRows, &numCols);
   playPaint(numRows, numCols);
   

   return 0;
 }


