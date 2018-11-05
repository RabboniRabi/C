/* Exercise program that converts hexadecimal to integer */
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

// Maximum number of digits that will be read
#define NUMBER_OF_DIGITS 5

/**
 * All the method declarations
 */
/* Helper method to check if the first character is '0' */
bool isFirstCharacterValid(char c);
/* Helper method to check if the second character is 'x' or 'X' */
bool isSecondCharacterValid(char c);
/* Helper method that returns the integer equivalent of a hexadecimal alphabet */
int getIntegerValueForUpperCaseHexadecimal(char hexadecimalChar);
/* Helper method that returns the integer equivalent of a hexadecimal alphabet */
int getIntegerValueForLowerCaseHexadecimal(char hexadecimalChar);
/* Method that reads the hexadecimal input with checks for validity */
void readHexadecimal();
/* Method that calculates the integer value of the digits stored in the array */
int calculateIntegerValue();


/* global variables */
// array storing the integer equivalent of each hexadecimal digit.
int inputDigits[NUMBER_OF_DIGITS];
// digits read counter
int digitCount = 0;


void main() {
  printf("%s\n", "Enter the hexadecimal number to be converted to integer.");
  printf("%s\n", "Maximum number of digits this program can handle is "
                  + NUMBER_OF_DIGITS);
  printf("%s\n", "Sample: 0x3Ed");
  readHexadecimal();

  int integerValue = calculateIntegerValue();
  printf("%s %d\n", "The decimal equivalent is: ", integerValue);
}

void readHexadecimal() {
  int c;
  bool firstCharacterRead = false;
  bool secondCharacterRead = false;
  while ((c = getchar()) != EOF) {
    // If first expected character has not been read
    if (!firstCharacterRead) {
       if (isFirstCharacterValid(c)) {
         firstCharacterRead = true;
       }
       else {
         break;
       }
    }
    // If second expected character has not been read
    else if (firstCharacterRead && !secondCharacterRead) {
      if (isSecondCharacterValid(c)) {
        secondCharacterRead = true;
      }
      else {
        break;
      }
    }
    // Read the digits that follow upto the NUMBER_OF_DIGITS
    else if (digitCount < NUMBER_OF_DIGITS) {

      if(isdigit(c)) {
        inputDigits[digitCount] = c - '0';
      }

      else if (c >= 'a' && c <= 'f') {
        inputDigits[digitCount] = getIntegerValueForLowerCaseHexadecimal(c);
      }

      else if (c >= 'A' && c <= 'F') {
        inputDigits[digitCount] = getIntegerValueForUpperCaseHexadecimal(c);
      }

      else { //not a valid character
        printf("%s\n", "Invalid input");
        break;
      }

      digitCount++;
    }
    else {
      printf("%s %d %s\n", "This program can only convert upto", NUMBER_OF_DIGITS, "digits.");
      break;
    }

  }

}


int calculateIntegerValue() {
  int integerValue = 0;
  int i = 0;
  while(digitCount > 0) {

    integerValue = integerValue + inputDigits[i] * (pow(16,digitCount-1));
    digitCount--;
    i++;
  }

  return integerValue;
}

bool isFirstCharacterValid(char c) {
  if (c == '0') {
    return true;
  }
  printf("%s\n", "First character is not valid. '0' expected.");
  return false;
}

bool isSecondCharacterValid(char c) {
  if (c == 'x' || c == 'X') {
    return true;
  }
  printf("%s\n", "Second character is not valid.'x' or 'X' expected.");
  return false;
}

int getIntegerValueForUpperCaseHexadecimal(char hexadecimalChar) {
  return hexadecimalChar - 'A' + 10;
}

int getIntegerValueForLowerCaseHexadecimal(char hexadecimalChar) {
  return hexadecimalChar - 'a' + 10;
}
