#include <stdio.h>


int getUserNum(const char* prompt) {
  int num = 0;

  printf("%s", prompt);
  scanf("%d", &num);
  return num;
}

void printCols(int columns[], int cols) {
  int c;
  for(c = 0; c< cols; c++) {
    printf("%d", columns[c]);
  }
}

void fillInCols(int columns[], int cols){
  int c;
  for(c = 0; c < cols; c++) {
    int num;
    scanf("%d", &num);
    columns[c] = num;
  }
}

void addArrayAToB(int columnsA[], int columnsB[], int cols){
  int c;
  for(c = 0; c < cols; c++) {
    columnsA[c] = columnsA[c] + columnsB[c];
    printf("%d", columnsA[c]);
    if (c < cols -1) {
      printf(" ");
    }
    else {
      printf("\n");
    }
  }
}

void createRowsOfMatrix() {
  int rows = getUserNum("Please enter the number of rows: ");
  int cols = getUserNum("Please enter the number of columns: ");

  int matrixA[rows][cols];
  int matrixB[rows][cols];

  int r;

  printf("Enter Matrix A\n");
  for (r = 0; r < rows; r++) {
    fillInCols(matrixA[r], cols);
  }

  printf("Enter Matrix B\n");
  for (r = 0; r < rows; r++) {
    fillInCols(matrixB[r], cols);
  }
  printf("A + B =\n");
  for (r = 0; r < rows; r++) {
    addArrayAToB(matrixA[r], matrixB[r], cols);
  }
}

int main() {

  createRowsOfMatrix();

  return 0;
}