#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "win.h"
#include "board.h"
#include "move.h"


void checkCommandLineInput(int argc, char* argv[], int* numRows, int* numCols, int* numPiecesToWin) {
  if (argc > 4) {
    printf("Too many arguments entered\n");
    printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
    exit(0);
  }
  else if (argc < 4) {
    printf("Not enough arguments entered\n");
    printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
    exit(0);
  }

  int i;
  for (i = 1; i <= 3; i++) {
    int num = atoi(argv[i]);
    if (num < 0) {
      printf("invalid arguments. should not be negative");
      exit(0);
    }
    else if (num == 0) {
      printf("invalid arguments, not an int");
      exit(0);
    }
    else {
      continue;
    }}

  *numRows = atoi(argv[1]);
  *numCols = atoi(argv[2]);
  *numPiecesToWin = atoi(argv[3]);

}

int main(int argc, char* argv[]) {
  int numRows, numCols, numPiecesToWin;

  checkCommandLineInput(argc, argv, &numRows, &numCols, &numPiecesToWin);

  const char pieces[] = "XO";
  const char blank_space = '*';
  char** board = create_board(numRows, numCols, blank_space);


  int player_turn = 0; // 0 means player 1, 1 means player

  display_board(board, numRows, numCols);

  while (!is_game_over(board, numRows, numCols, blank_space, pieces[player_turn], numPiecesToWin)) {
    int colPicked = getColPicked(numCols, board);

    makeMove(board, colPicked, numRows, pieces[player_turn]);

    display_board(board, numRows, numCols);

    player_turn = declare_winner_or_tie(player_turn, board, numRows, numCols, blank_space, pieces[player_turn], numPiecesToWin);

  }

  clean_up(&board, numRows);

  return 0;
}