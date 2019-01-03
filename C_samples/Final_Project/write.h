//
// Created by Mira Mastoras on 12/8/17.
//
#include "command.h"
#include "board.h"
#include <stdbool.h>
#ifndef FINALPROJECT_WRITE_H
#define FINALPROJECT_WRITE_H

void drawLToR_Horizontal(Board* theBoard, writeCommands* writeCommandsP);
void drawRToL_Horizontal(Board *theBoard, writeCommands *writeCommandsP);
void drawTopDownVertical(Board* theBoard, writeCommands* writeCommandsP);
void drawBottomUpVertical(Board *theBoard, writeCommands *writeCommandsP);
void drawLToR_RightDiag(Board* theBoard, writeCommands* writeCommandsP);
void drawRToL_RightDiag(Board* theBoard, writeCommands* writeCommandsP);
void drawLToR_LeftDiag(Board* theBoard, writeCommands* writeCommandsP);
void drawRToL_LeftDiag(Board* theBoard, writeCommands* writeCommandsP);

void commandWrite(Board* theBoard, writeCommands* writeCommandsP);

#endif //FINALPROJECT_WRITE_H
