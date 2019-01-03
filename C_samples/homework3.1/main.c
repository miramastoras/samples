#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;

  do{
    scanf("%c", &character);
    if(!isspace(character)){
      formatIsGood = false;
    }
    //formatIsGood = formatIsGood && isspace(character);
    //formatIsGood = isspace(character) ? formatIsGood : false;
  }while(character != '\n');

  return formatIsGood;

}

int getValidInt(const char* prompt){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num);
  }while(!isValidFormat(numArgsRead, numArgsNeeded));

  return num;
}

int getPosInt(const char* prompt){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num);
  }while(!(isValidFormat(numArgsRead, numArgsNeeded) &&
      num > 0));

  return num;
}

int main() {
  int seedNum = getValidInt("Enter the seed for the random number generator: ");
  int numIterations = getPosInt("Enter the number of iterations to run: ");

  return 0;
}