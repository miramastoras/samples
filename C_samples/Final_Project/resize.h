//
// Created by Mira Mastoras on 12/12/17.
//

#include "board.h"
#include "command.h"
#ifndef FINALPROJECT_RESIZE_H
#define FINALPROJECT_RESIZE_H
void commandResize(Board* theBoard, RowAndCol* resizeCommandsP);
void addNewRowAt(int position, Board* theBoard);
void commandDelete(Board *theBoard, addOrDelete *deleteCommandsP);

void commandAdd(Board* theBoard, addOrDelete* addCommandsP);
#endif //FINALPROJECT_RESIZE_H
