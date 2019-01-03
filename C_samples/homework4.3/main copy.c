#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void copyAtoBString(char* stringA, char* stringB){
  int x;

  for (x = 0; x < strlen(stringB); x++) {
    stringB[x] = stringA[x];
  }
}
void convertToLower(char* userStrA) {
  int c;
  for (c = 0; c < strlen(userStrA); c++) {
    userStrA[c] = tolower(userStrA[c]);
  }
}

void getUserStr(const char* prompt, char* userStr) {
  printf("%s", prompt);
  scanf("%s", userStr);
}

void checkIfAnagram(char* userStrA, char* userStrB) {

  convertToLower(userStrA);
  convertToLower(userStrB);

  if (strlen(userStrA) != strlen(userStrB)) {
    printf("%s is NOT an anagram of %s", userStrA, userStrB);
    exit(0);
  }
  else {
    int c, r;
    //int x;

    char copyOfB[strlen(userStrB)];
    copyAtoBString(userStrB, copyOfB);

    //for (x = 0; x < strlen(userStrB); x++) {
     // copyOfB[x] = userStrB[x];
   // }

    for (c = 0; c < strlen(userStrA); c++) {

      bool matchFound = false;

      for (r = 0; r < strlen(copyOfB); r++) {
          if (userStrA[c] == copyOfB[r]){
            copyOfB[r] = '0';
            matchFound = true;
            break;
          }
      }

      if (!matchFound) {
        printf("%s is NOT an anagram of %s", userStrA, userStrB);
        exit(0);
      }
    }
    printf("%s is an anagram of %s", userStrA, userStrB);
  }
}

int main() {
  char userStrA[20];
  char userStrB[20];

  getUserStr("Please enter the first word: ", userStrA);
  getUserStr("Please enter the second word: ", userStrB);


  checkIfAnagram(userStrA, userStrB);

  return 0;
}