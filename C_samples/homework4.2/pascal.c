#include <stdio.h>

int getUserInput(const char* prompt) {

  int numRows;
  printf("%s", prompt);
  scanf("%d", &numRows);
  return numRows;
};


void fillInPascalTri(int numLevels){
  int pascalTri[28][28];
  int numRows, numCols;
  int r, c;

  numRows = numLevels;
  numCols = 1;

  for (r = 0; r < numRows; r++) {
    for (c = 0; c < numCols; c++) {

      if (c == 0 || r == c) {
        pascalTri[r][c] = 1;
      }

      else {
        pascalTri[r][c] = pascalTri[r - 1][c - 1] + pascalTri[r -1][c] ;
      }
      printf("%d ", pascalTri[r][c]);
    }
    printf("\n");
    numCols = numCols + 1;
  }
}

int main() {

  int numLevels = getUserInput("Please enter how many levels of Pascal's Triangle you would like to see: ");

  fillInPascalTri(numLevels);

  return 0;
}