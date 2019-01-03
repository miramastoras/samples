//
// Created by Mira Mastoras on 11/15/17.
//

#ifndef HOMEWORK5_2_WIN_H
#define HOMEWORK5_2_WIN_H
#include <stdbool.h>
bool is_game_over(char** board,
                  const int num_rows, const int num_cols,
                  const char blank_space, const char pieces, const int numPiecesToWin);
bool win(char** board, const int num_rows, const int num_cols,
         const char blank_space, const char pieces, const int numPiecesToWin);
bool horz_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin);
bool vert_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin);
bool diag_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin);
bool left_diag_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin);
bool right_diag_win(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin);

bool tie(char** board, const int num_rows, const int num_cols, const char blank_space, const char pieces, const int numPiecesToWin);
bool is_board_full(char** board, const int num_rows, const int num_cols, const int blank_space);

int declare_winner_or_tie(const int player_turn,
                           char** board,
                           const int num_rows,
                           const int num_cols,
                           const char blank_space, const char pieces, const int numPiecesToWin);


bool numPiecesInARow(char* array, const int len, const char pieces, const int numPiecesToWin);
int changeTurn(int playerTurn);

#endif //HOMEWORK5_2_WIN_H
