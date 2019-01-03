//
// Created by Mira Mastoras on 11/15/17.
//

#include "win.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


bool is_game_over(char** board, const int num_rows, const int num_cols, const char blank_space,const char pieces, const int numPiecesToWin) {
  return win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin) ||
      tie(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin);
}

int declare_winner_or_tie(const int player_turn,
                           char** board,
                           const int num_rows,
                           const int num_cols,
                           const char blank_space, const char pieces, const int numPiecesToWin) {

  if(win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin)){
    if(player_turn == 0){
      printf("Player 1 Won!\n");
      return player_turn;
    }else{
      printf("Player 2 Won!\n");
      return  player_turn;
    }
  }
  else if (tie(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin)) {
    printf("Tie game!\n");
    return player_turn;
  }
  else{
    return changeTurn(player_turn);
  }
}

int changeTurn(int playerTurn) {
  if (playerTurn == 0) {
    return 1;
  }
  else  {
    return 0;
  }
}

bool win(char** board, const int num_rows, const int num_cols, const char blank_space,const char pieces, const int numPiecesToWin) {
  return horz_win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin) ||
      vert_win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin) ||
      diag_win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin);
}

bool horz_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin) {

  for(int row = 0; row < num_rows; ++row){
    if(numPiecesInARow(board[row], num_cols, pieces, numPiecesToWin)){
      return true;
    }
  }
  return false;
}

bool vert_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin) {
  char* col_to_check = (char*)malloc(num_rows* sizeof(char));

  for(int col = 0; col < num_cols; ++col){

    for(int row = 0; row < num_rows; ++row){
      col_to_check[row] = board[row][col];
    }
    if(numPiecesInARow(col_to_check, num_rows, pieces, numPiecesToWin)){
      free(col_to_check);
      return true;
    }
  }
  free(col_to_check);
  return false;
}

bool diag_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin) {
  return left_diag_win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin) ||
      right_diag_win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin);
}

/**
 * Check for wins that look like
 * X
 *   X
 *     X
 * assuming a square board
 * @param board
 * @param num_rows
 * @param num_cols
 * @param blank_space
 * @return
 */
bool left_diag_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin) {
  char* diag = (char*)malloc(num_rows * sizeof(char));

  for(int pos = 0; pos < num_rows; ++pos){
    diag[pos] = board[pos][pos];
  }

  bool did_win = numPiecesInARow(diag, num_rows, pieces, numPiecesToWin);

  free(diag);
  return did_win;
}

/**
 * check for wins that look like
 *     X
 *    X
 *   X
 * assuming square board
 * @param board
 * @param num_rows
 * @param num_cols
 * @param blank_space
 * @return
 */
bool right_diag_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin) {
  char* diag = (char*)malloc(num_rows * sizeof(char));

  for(int pos = 0; pos < num_rows; ++pos){
    diag[pos] = board[pos][num_cols - 1  - pos];
  }

  bool did_win = numPiecesInARow(diag, num_rows, pieces, numPiecesToWin);

  free(diag);
  return did_win;
}

bool tie(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin) {
  return !win(board, num_rows, num_cols, blank_space, pieces, numPiecesToWin) &&
      is_board_full(board, num_rows, num_cols, blank_space);
}

bool is_board_full(char** board, const int num_rows, const int num_cols, const int blank_space) {
  for(int row = 0; row < num_rows; ++row){
    for(int col = 0; col < num_cols; ++col){
      if(board[row][col] == blank_space){
        return false;
      }
    }
  }
  return true;
}




bool numPiecesInARow(char* array, const int len, const char pieces, const int numPiecesToWin) {
  int numInARow = 0;

  for(int i = 0; i < len; ++i){
    if(array[i] == pieces){
      numInARow = numInARow + 1;
      if (numInARow == numPiecesToWin) {
        return true;
      }
    }
    else {
      numInARow = 0;
    }
  }
  return false;
}
