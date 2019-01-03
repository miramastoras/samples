//
// Created by Mira Mastoras on 11/24/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "read_lines.h"

char* readSingleLine(FILE* fp) {
  char c;
  char* array = NULL;
  int i = 1;
  fscanf(fp, "%c", &c);
  while(!feof(fp)){
    if (c == '\n') {
      array = (char*)realloc(array, sizeof(char) * i);
      array[i - 1] = c;
      break;
    }
    else {
      array = (char*)realloc(array, sizeof(char) * i);
      array[i - 1] = c;
      i++;
      fscanf(fp, "%c", &c);
    }
  }
  i++;
  array = (char*)realloc(array, sizeof(char) * i);
  array[i - 1] = '\0';
  return array;
}


void read_lines(FILE *fp, char ***lines, int *num_lines) {
  int c = 0;
  int i  = 1;

  *lines = (char**)malloc(sizeof(char*) * (1));

  while (!(feof(fp))){
    //line = readSingleLine(fp);

    *lines = (char**)realloc(*lines, sizeof(char*) * i);
    (*lines)[c] = readSingleLine(fp);

   // printf("line in array: %d: %s\n",c, (*lines)[c]);
    i++;
    c++;
  }

  *num_lines = c - 1;
}






  /**while (!(feof(fp))){

  }



  fseek(fp, 0, SEEK_SET);

 while (!(feof(fp))){
    (*lines)[c] = (char *)malloc(sizeof(char*) * 1000);
    fgets((*lines)[c], 1000, fp);

    printf("line %d: %s\n",c, (*lines)[c]);
    c++;
  }

  *num_lines = c ;**/




