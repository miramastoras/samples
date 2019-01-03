//
// Created by Mira Mastoras on 11/15/17.
//

#ifndef HOMEWORK5_2_MOVE_H
#define HOMEWORK5_2_MOVE_H
int getColPicked(const int numCols, char** board);
void makeMove(char** board, const int colPicked, const int numRows, const char pieces);
int changeTurn(int playerTurn);
#endif //HOMEWORK5_2_MOVE_H
