#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char userConversionChoice ();

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
    printf("Invalid formatting. Ending program.\n");
    exit(0);
  }
}

// convert celsius to unit desired
double convertCelsiusToOtherUnit(double celsiusValue, char userUnit, double userValue) {
  char newUnit;
  double newValue;
  printf("Enter the new unit type (F, C, or K): ");
  newUnit = getValidChar(true);

  if (newUnit == 'F' || newUnit == 'f') {
    newValue = celsiusValue * (9.0 / 5.0 ) + 32.0;
    newUnit = 'F';
  }
  else if (newUnit == 'C' || newUnit == 'c') {
    newValue = celsiusValue;
    newUnit = 'C';
  }
  else if (newUnit == 'K' || newUnit == 'k') {
    newValue = celsiusValue + 273.15;
    newUnit = 'K';
  }
  else {
    printf("%c is not a valid temperature type. Ending program.\n", newUnit);
    exit(0);
  }

  printf("%.2lf%c is %.2lf%c\n", userValue, userUnit, newValue, newUnit );
  return(0);
}

// convert yards to unit desired
double convertYardsToOtherUnit(double yardsValue, char userUnit, double userValue) {
  char newUnit;
  double newValue;
  printf("Enter the new unit type (I,F,Y,M): ");
  newUnit = getValidChar(true);

  if (newUnit == 'I' || newUnit == 'i') {
    newValue = yardsValue * 36.0;
    newUnit = 'I';
  }
  else if (newUnit == 'F' || newUnit == 'f') {
    newValue = yardsValue * 3.0;
    newUnit = 'F';
  }
  else if (newUnit == 'Y' || newUnit == 'y') {
    newValue = yardsValue;
    newUnit = 'Y';
  }
  else if (newUnit == 'M' || newUnit == 'm') {
    newValue = yardsValue / 1760.0;
    newUnit = 'M';
  }
  else {
    printf("%c is not a valid distance type. Ending program.\n", newUnit);
    exit(0);
  }

  printf("%.2lf%c is %.2lf%c\n", userValue, userUnit, newValue, newUnit );
  return(0);
}

// converts user Unit to celsius or yards
double convertUserUnit(char userUnit, char conversionType, double userValue) {
  double newCelsiusValue;
  double newYardsValue;
  if (conversionType == 'd' || conversionType == 'D') {
    if (userUnit == 'I' || userUnit =='i') {
      newYardsValue = userValue / 36.0;
      return newYardsValue;
    }
    else if (userUnit == 'F' || userUnit == 'f') {
      newYardsValue = userValue / 3.0;
      return newYardsValue;
    }
    else if (userUnit =='y' || userUnit == 'Y' ) {
      newYardsValue = userValue;
      return newYardsValue;
    }
    else if (userUnit == 'M' || userUnit == 'm'){
      newYardsValue = 1760.0 * userValue;
      return newYardsValue;
    }
    else {
      printf("%c is not a valid distance type. Ending program.\n", userUnit);
      exit(0);
    }
  }
  if (conversionType == 't' || conversionType =='T') {
    if (userUnit == 'F' || userUnit == 'f') {
      newCelsiusValue = (userValue - 32.0) * (5.0/9.0) ;
      return newCelsiusValue;
    }
    else if (userUnit == 'C' || userUnit == 'c') {
      newCelsiusValue = userValue;
      return newCelsiusValue;
    }
    else if (userUnit == 'K' || userUnit == 'k') {
      newCelsiusValue = userValue - 273.15;
      return newCelsiusValue;
    }
    else {
      printf("%c is not a valid temperature type. Ending program.\n", userUnit);
      exit(0);
    }
  }
  return (0);
}

/** directs to correct path: distance or temperature
 *
 * @param conversionType
 * reads in and checks input for conversion type and user input of number
 * @return
 */
double directToPath (char conversionType) {
  double userTempInCelsius;
  double userDistInYards;
  double userValue = 0.0;
  char userUnit = 'a';

  if (conversionType == 'D'|| conversionType =='d') {
    printf("Enter the distance followed by its suffix (I,F,Y,M): ");
    userValue = getValidDouble(false);
    userUnit = getValidChar(true);
    if (userUnit == 'F' || userUnit == 'f' ){
      userUnit = 'F';
    }
    else if (userUnit == 'I' || userUnit == 'i') {
      userUnit = 'I';
    }
    else if (userUnit =='Y' || userUnit == 'y') {
      userUnit = 'Y';
    }
    else if (userUnit == 'M'|| userUnit == 'm') {
      userUnit = 'M';
    }
    else {
      userUnit = userUnit;}

    userDistInYards = convertUserUnit(userUnit, conversionType, userValue);
    convertYardsToOtherUnit(userDistInYards, userUnit, userValue);
  }
  else if (conversionType == 'T' || conversionType == 't') {
    printf("Enter the temperature followed by its suffix (F, C, or K): ");
    userValue = getValidDouble(false);
    userUnit = getValidChar(true);
    if (userUnit == 'F' || userUnit == 'f' ){
      userUnit = 'F';
    }
    else if (userUnit == 'C' || userUnit == 'c') {
      userUnit = 'C';
    }
    else if (userUnit =='K' || userUnit == 'k') {
      userUnit = 'K';
    }
    else {
      userUnit = userUnit;
    }
    userTempInCelsius = convertUserUnit(userUnit, conversionType, userValue);
    convertCelsiusToOtherUnit(userTempInCelsius, userUnit, userValue);
  }
  else {
    printf("Unknown conversion type %c chosen. Ending program.\n", conversionType);
    exit(0);
  }
  return (0);
}

char userConversionChoice () {
  char conversionType = 'a';

  printf("Pick the type of conversion that you would like to do.\n");
  printf("T or t for temperature\n");
  printf("D or d for distance\n");

  printf("Enter your choice: ");
  conversionType = getValidChar(true);

  return conversionType;
}

int main() {
  char conversionType;
  conversionType = userConversionChoice();

  directToPath(conversionType);
  return 0;
}