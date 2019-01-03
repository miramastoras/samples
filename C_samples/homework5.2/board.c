//
// Created by Mira Mastoras on 11/15/17.
//

#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

void display_board(char** board, const int num_rows, const int num_cols) {

  int label = num_rows - 1;
  // print board
  for (int row = 0; row < num_rows; ++row) {
    printf("%d ", label);
    for (int col = 0; col < num_cols; ++col) {
      printf("%c ", board[row][col]);
    }
    label = label - 1;
    printf("\n");
  }
  printf("  ");
  for(int col = 0; col < num_cols; ++col) {
    printf("%d ", col);
  }
  printf("\n");
}

char** create_board(const int num_rows, const int num_cols, const char blank_space) {
  char** board = (char**) malloc(num_rows * sizeof(char*));
  for(int row = 0; row < num_rows; ++row){
    board[row] = (char*) malloc(num_cols * sizeof(char));
    for (int col = 0; col < num_cols; ++col) {
      board[row][col] = blank_space;
    }
  }
  return board;
}

void clean_up(char*** board, const int num_rows) {
  for(int row = 0; row < num_rows; ++row){
    free((*board)[row]);
  }
  free(*board);
  *board = NULL;
}

