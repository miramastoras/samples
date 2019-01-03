#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// take array and do recursion onto it

void print_ar(char* ar, int len);
void _rec_bin_string(int lenBinStr, char* binarystring, char* cur_string, int index);



void rec_bin_string(int lenBinStr, char* binarystring) {
  char* cur_string = (char*)malloc((lenBinStr + 1) * sizeof(char));
  cur_string[lenBinStr] = '\0';
  _rec_bin_string(lenBinStr, binarystring, cur_string, 0);

  free(cur_string);
}

void _rec_bin_string(int lenBinStr, char* binarystring, char* cur_string, int index) {

  if (binarystring[0] == '\0') {
    print_ar(cur_string, lenBinStr);
  } else {
    if (binarystring[0] == '1' || binarystring[0] == '0') {
      cur_string[index] = binarystring[0];
      _rec_bin_string(lenBinStr, binarystring + 1, cur_string, index + 1);
    } else {
      cur_string[index] = '0';
      _rec_bin_string(lenBinStr, binarystring + 1, cur_string, index + 1);
      cur_string[index] = '1';
      _rec_bin_string(lenBinStr, binarystring + 1, cur_string, index + 1);
    }
  }
}
void print_ar(char *ar, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%c", ar[i]);
  }
  printf("\n");
}




int main(int argc, char* argv[]) {
  int lenBinStr = strlen(argv[1]);
  char* binaryString = (char*) malloc((lenBinStr + 1) * sizeof(char));
  strcpy(binaryString, argv[1]);

  rec_bin_string(lenBinStr, binaryString);
  free(binaryString);

  return 0;
}