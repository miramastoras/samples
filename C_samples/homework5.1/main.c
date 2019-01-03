#include <stdio.h>
#include <stdlib.h>

int getUserNum(const char* prompt) {
  int num = 0;

  printf("%s", prompt);
  scanf("%d", &num);
  return num;
}

void printMatrix(int** mat, const int num_rows, const int num_cols, const char* prompt) {

  printf("%s\n", prompt);
  for (int row = 0; row < num_rows; ++row) {
    for (int col = 0; col < num_cols; ++col) {
      printf("%3d ", mat[row][col]);
    }
    printf("\n");
  }
}

void delete_table(int*** mat, const int num_rows, const int num_cols) {
  for (int row = 0; row < num_rows; ++row) {
    free((*mat)[row]);
  }
  free(*mat);
  *mat = NULL;
}

int** makeMatrix(const int num_rows, const int num_cols, const char* prompt) {
  int** table = (int**) malloc(num_rows * sizeof(int*));

  printf("%s\n", prompt);

  for (int row = 0; row < num_rows; ++row) {
    table[row] = (int*) malloc(num_cols * sizeof(int));
    for (int col = 0; col < num_cols; ++col) {
      scanf("%d", &table[row][col]);
    }
  }
  return table;
}

int** addMatrixBIntoA(int** matrixA, int** matrixB,const int numRows, const int numCols) {
  int r, c;

  for(r = 0; r < numRows; r++){
    for(c = 0; c < numCols; c++){
      matrixA[r][c] = matrixB[r][c] + matrixA[r][c];
    }
  }

  return matrixA;
}

int main() {
  int numRows, numCols;

  numRows = getUserNum("Please enter the number of rows: ");
  numCols = getUserNum("Please enter the number of columns: ");

  int** matrixA = makeMatrix(numRows, numCols, "Enter Matrix A" );
  int** matrixB = makeMatrix(numRows, numCols, "Enter Matrix B");

  matrixA = addMatrixBIntoA(matrixA, matrixB, numRows, numCols);

  printMatrix(matrixA, numRows, numCols, "A + B =");

  delete_table(&matrixA, numRows, numCols);
  delete_table(&matrixB, numRows, numCols);

  return 0;
}