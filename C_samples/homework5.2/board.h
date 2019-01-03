//
// Created by Mira Mastoras on 11/15/17.
//

#ifndef HOMEWORK5_2_BOARD_H
#define HOMEWORK5_2_BOARD_H
void display_board(char** board, const int num_rows, const int num_cols);
char** create_board(const int num_rows, const int num_cols, const char blank_space);
void clean_up(char*** board, const int num_rows);

#endif //HOMEWORK5_2_BOARD_H
