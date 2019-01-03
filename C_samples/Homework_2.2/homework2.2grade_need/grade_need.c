#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// define all functions

/**
 *
 * @param numArgsNeeded: the number of format placeholders that needed to have been read in the last scanf
 * @param numArgsRead: the actual number of placeholders that were read from scanf, ie its return value
 * @param isLastElementOnLine: true if this is the last value that should be on this line of input
 * @return: true if the input is correctly formatted and false otherwise
 */
bool isValidInput(const int numArgsNeeded, const int numArgsRead, const bool isLastElementOnLine) {

  char lastCharacterOnLine;

  // did we read everything we needed to read?
  bool correctFormat = numArgsRead == numArgsNeeded;

  if (isLastElementOnLine) {  // if this is supposed to be the last thing on the line
    // check that it was by reading one more character
    // and seeing it it a newline (the end of the line)
    scanf("%c", &lastCharacterOnLine);
    correctFormat = correctFormat && lastCharacterOnLine == '\n';
  }

  return correctFormat;
}


/**
 * Get a double from the user but close the program if one is not entered
 * @param isLastElementOnLine : true if this is the last value that should be on this line of input
 * @return a valid double
 */
double getValidDouble(const bool isLastElementOnLine) {
  const int numArgsNeeded = 1;
  int numArgsRead;
  double num;

  numArgsRead = scanf(" %lf", &num);
  if (isValidInput(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    return num;
  } else {
    printf("Invalid formatting. Ending program.");
    exit(0);
  }
}

/**
 * Get a double between lower bound and upper bound inclusive
 * @param lowerBound
 * @param upperBound
 * @param isLastElementOnLine : true if this is the last value that should be on this line of input
 * @return
 */
double getValidDoubleInRange(const double lowerBound, const double upperBound, const bool isLastElementOnLine) {
  // first get a valid double
  double num = getValidDouble(isLastElementOnLine);

  // then check that it meets the constraints
  if (num >= lowerBound && num <= upperBound) {
    return num;
  }
  else if (num < 0){
    printf("The number you last entered should have been positive. Ending program.\n");
    exit(0);
  }

  else {
    printf("Invalid formatting. Ending program.");
    exit(0);
  }
}

// get valid char
/**
 * Get a character  from the user but close the program if one is not entered
 * @param isLastElementOnLine : true if this is the last value that should be on this line of input
 * @return a valid character
 */
char getValidChar(const bool isLastElementOnLine) {
  const int numArgsNeeded = 1;
  int numArgsRead;
  char theCharacter;

  numArgsRead = scanf(" %c", &theCharacter);
  if (isValidInput(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    return theCharacter;
  } else {
    printf("Invalid formatting. Ending program.\n");
    exit(0);
  }
}
// calculate the grade needed

double calcGradeNeeded(double percent_needed, double final_weight, double current_percent, char desiredGradeLetter ) {
  double grade = 0.0;
  grade = (100 * percent_needed - (100 - final_weight) * current_percent) / final_weight ;

  if (grade > 100) {
    printf("You cannot get a %c in the class because you would need to score\n"
               "at least %.2lf%% on the final.", desiredGradeLetter, grade);
  }
  else if (grade < 0) {
    printf("You cannot score low enough on the final to get a %c in the class.", desiredGradeLetter);
  }
  else {
    printf("You need a grade of at least %.2lf%% on the final to get a %c in the class.", grade, desiredGradeLetter);
  }
  return grade;
}

// the following functions get user input & check if it is valid:

// get desired grade letter & convert to percent
char getDesiredGradeLetter() {
  char desiredLetter;
  printf("Enter the grade you want in the class: ");

  desiredLetter = getValidChar(true);

  return desiredLetter;
}

double getDesiredGradePercent(char desiredGradeLetter) {
  double desiredPercent = 0.0;

  if (desiredGradeLetter == 'A' || desiredGradeLetter == 'a') {
    desiredPercent = 90.00;
  }
  else if (desiredGradeLetter == 'B' || desiredGradeLetter == 'b') {
    desiredPercent = 80.00;
  }
  else if (desiredGradeLetter == 'C' || desiredGradeLetter == 'c') {
    desiredPercent = 70.00;
  }
  else if (desiredGradeLetter == 'D' || desiredGradeLetter == 'd') {
    desiredPercent = 60.00;
  }
  else if (desiredGradeLetter == 'F' || desiredGradeLetter == 'f') {
    desiredPercent = 0.00;
  }
  else {
   printf("Unknown Grade Received: %c. Ending program.", desiredGradeLetter);
    exit(0);
  }
  return desiredPercent;
}

// get current percent
double getCurrentPercent() {
  double currentPercent = 0.0;
  printf("Enter your current percent in the class: ");
  currentPercent = getValidDoubleInRange(0.0,100.0,true);
  return currentPercent;
}

// get weight of final
double getFinalWeight() {
  double finalWeight = 0.0;
  printf("Enter the weight of the final: ");
  finalWeight = getValidDoubleInRange(0.0,100.0,true);
  return finalWeight;
}

int main() {
  char desiredGradeLetter = 'a';
  double desiredGradePercent = 0.0;
  double currentPercent = 0.0;
  double finalWeight = 0.0;

  desiredGradeLetter = getDesiredGradeLetter();
  desiredGradePercent = getDesiredGradePercent(desiredGradeLetter);
  currentPercent = getCurrentPercent();
  finalWeight = getFinalWeight();

  calcGradeNeeded(desiredGradePercent, finalWeight, currentPercent, desiredGradeLetter);

  return 0;
}