#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void wordCount(char* fileName){
  FILE* src = fopen(fileName, "r");
  char c;
  int counter = 0;
  bool wasLastCharASpace = false;
  while(!feof(src)){
    fscanf(src, "%c", &c);
    if (isspace(c) || c == '\n'){
      if (!wasLastCharASpace) {
        counter++;
      }
      wasLastCharASpace = true;
    }
    else {
      wasLastCharASpace = false;
    }
  }
  printf("There are %d word(s).\n", counter);

  fclose(src);
  
}
int main(int argc, char** argv) {
  wordCount(argv[1]);


  return 0;
}