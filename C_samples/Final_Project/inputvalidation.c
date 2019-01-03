//
// Created by Mira Mastoras on 12/8/17.
//

#include "inputvalidation.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do {
    scanf("%c", &character);
    if (!isspace(character)) {
      formatIsGood = false;
    }
    formatIsGood = formatIsGood && isspace(character); //formatIsGood = isspace(character) ? formatIsGood : false;
  }while(character != '\n');
  return formatIsGood; }


/**bool isValidFormat() {
  bool formatIsGood = true;
  char character;
  do {
    scanf("%c", &character);
    if (!isspace(character)) {
      formatIsGood = false;
    } //formatIsGood = formatIsGood && isspace(character); //formatIsGood = isspace(character) ? formatIsGood : false;
  }while(character != '\n');
  return formatIsGood;
}**/


bool isAddInRange(addOrDelete *addCommandsP, const int numRows, const int numCols) {
  bool isAddInRange = false;
  if((*addCommandsP).rowOrColChar == 'r' || (*addCommandsP).rowOrColChar == 'c') {
    if((*addCommandsP).rowOrColChar == 'r') {
      if((*addCommandsP).rowOrColInt >= 0 && (*addCommandsP).rowOrColInt <= numRows + 1 ) {
        isAddInRange = true;
      }
    }
    else if((*addCommandsP).rowOrColChar == 'c') {
      if((*addCommandsP).rowOrColInt >= 0 && (*addCommandsP).rowOrColInt <= numCols + 1 ) {
        isAddInRange = true;
      }
    }
  }
  else {
    isAddInRange = false;
  }
  return isAddInRange;
}
bool isLoadFileValid(char *loadFileName) {
  FILE* file = fopen(loadFileName, "r");

  if(file == NULL){
    printf("Failed to open file: %s\n", loadFileName);
    return false;
  }
  fclose(file);
  return true;
}
bool isDeleteInRange(addOrDelete *deleteCommandsP, const int numRows, const int numCols) {
  bool isDelInRange = false;
  if((*deleteCommandsP).rowOrColChar == 'r' || (*deleteCommandsP).rowOrColChar == 'c') {
    if((*deleteCommandsP).rowOrColChar == 'r') {
      if((*deleteCommandsP).rowOrColInt >= 0 && (*deleteCommandsP).rowOrColInt < numRows ) {
        isDelInRange = true;
      }
    }
    else if((*deleteCommandsP).rowOrColChar == 'c') {
      if((*deleteCommandsP).rowOrColInt >= 0 && (*deleteCommandsP).rowOrColInt < numCols ) {
        isDelInRange = true;
      }
    }
  }
  else {
    isDelInRange = false;
  }
  return isDelInRange;
}
bool isWriteInRange(writeCommands *writeCommandsP, const int numRows, const int numCols) {
  if ( ((*writeCommandsP).startRow >= 0 && (*writeCommandsP).startRow < numRows)
      && ((*writeCommandsP).startCol >= 0 && (*writeCommandsP).startCol < numCols)
      && ((*writeCommandsP).endRow >= 0 && (*writeCommandsP).endRow < numRows)
      && ((*writeCommandsP).endCol >= 0 && (*writeCommandsP).endCol < numCols)){
  return true;
  }
  else {
    return false;
  }
}

bool isInRange(int userRow, int userCol, const int numRows, const int numCols) {
  if (userRow >= 0 && userRow < numRows && userCol >= 0 && userCol < numCols) {
    return true;
  }
  else{
    return false;
  }
}

bool isResizeInRange(RowAndCol *resizeCommandsP, const int numRows, const int numCols) {
  if ((*resizeCommandsP).Row >= 1 && (*resizeCommandsP).Col >= 1){
    return true;
  }
  else {
    return false;
  }
}
