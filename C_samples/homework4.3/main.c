#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isAnagram(char* userStrA, char* userStrB);


void copyAtoBString(char* stringA, char* stringB){
  int x;

  for (x = 0; x < strlen(stringA); x++) {
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

void checkIsAnagram(char* userStrA, char* userStrB){

  char stringAToCheck[20];
  char stringBToCheck[20];

  copyAtoBString(userStrA, stringAToCheck);
  copyAtoBString(userStrB, stringBToCheck);

  if (isAnagram(stringAToCheck, stringBToCheck)) {
    printf("%s is an anagram of %s\n", userStrA, userStrB);
  }
  else {
    printf("%s is NOT an anagram of %s\n", userStrA, userStrB);
  }
}

bool isAnagram(char* userStrA, char* userStrB) {

  convertToLower(userStrA);
  convertToLower(userStrB);

  if (strlen(userStrA) != strlen(userStrB)) {
    return false;
  }
  else {
    int c, r;

    char copyOfB[strlen(userStrB)];
    copyAtoBString(userStrB, copyOfB);

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
        return false;
      }
    }
  }
  return true;
}

int main() {
  char userStrA[20];
  char userStrB[20];

  getUserStr("Please enter the first word: ", userStrA);
  getUserStr("Please enter the second word: ", userStrB);

  checkIsAnagram(userStrA, userStrB);

  return 0;
}