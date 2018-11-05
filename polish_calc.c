/**
 * Implementing for practise,
 * a basic polish style calculator
 * largely referenced from the same program in
 * the C Programming Langugage book.
 *
 * This program can perform addition, subtraction,
 * division, multiplication and modulo operation.
 * Example: In order to perform the operation:
 * (((8 * 3) % 5) + 3), enter 8 3 * 5 % 3 +
 *
 * @author Rabboni Rabi
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXOP 100 /* Maximum allowed size of operand or operator */
#define MAXVAL 100 /* Maximum depth of stack holding operand values */
#define BUFFSIZE 100 /* Buffer for ungetCh() */
#define NUMBER '0' /* Signal that a number was found */

int stackPos = 0; /* Next free stack position */
int bufferPos = 0; /* Next free buffer position */
char buff[BUFFSIZE]; /* Buffer for ungetCh() */
double val[MAXVAL]; /* Values stack */

/* Declare helper functions to be used */
int getOp(char []); /* Get the next operand or operator */
void push(double); /* Push a value to a stack */
double pop(void); /* Pop and return a value from a stack */
int getCh(void); /* Get next character (pushed back or from stream) */
void ungetCh(int); /* Push character back on input */

int main() {

  int type; /* variable to hold the next operand or operator */
  double op2; /* variable to hold second operand */
  char s[MAXOP]; /* variable to hold array of digits of the operand read */

  /* While next operand or operator is not end-of-file */
  while ((type = getOp(s)) != EOF) {

    switch (type) {

      /* If operand, push to stack */
      case NUMBER:
        push(atof(s));
        break;

      /* If type is an operator, pop the two operands on the stack,
       * perform the operation between two and push it back to the stack */
      case '+':
        push(pop() + pop());
        break;

      /* If subtraction, pop the second operand first to ensure order */
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;

      case '*':
       push(pop() * pop());
       break;

      /* If division, pop the second operand first to ensure order */
      case '/':
       op2 = pop();
       if (op2 != 0.0) {
         push(pop() / op2);
       } else {
         printf("%s\n", "Cannot divide by 0");
       }
       break;

       /* If modulo division, pop the second operand first to ensure order */
      case '%':
       op2 = pop();
       if (op2 != 0.0) {
          push(fmod(pop(), op2));
       } else {
         printf("%s\n", "Cannot take modulo when the divisor is 0");
       }
       break;

       /* If new line is read, pop & print the value in the top of the stack */
       case '\n':
       printf("\t%.8g\n", pop());
       break;

      default:
       printf("Error: Unrecognised command: %s\n", s);
       break;
    }
  }

  return 0;
}

/* Pushes the operand value to top of the stack */
void push(double op) {
  if (stackPos < MAXVAL) {
    val[stackPos++] = op;
  }
  else {
    printf("Error: stack full, cannot push: %g\n", op);
  }
}

/* Pops the last pushed operand value from the stack */
double pop() {
  if (stackPos > 0) {
    return val[--stackPos];
  }
  else {
    printf("Error: stack is empty, cannot pop\n");
    return 0.0;
  }

}
  /* Get the next operator or numeric command */
  int getOp(char s[]) {

    int i, c;

    while ((s[0] = c = getCh()) == ' ' || c == '\t') {
      // Skip blanks and tabs
    }
    s[1] = '\0';
    i = 0;

    /* If it is not a number, return the character */
    if (!isdigit(c) && c != '.') {
      return c;
    }

    if (isdigit(c)) {
      while (isdigit(s[++i] = c = getCh())) {
        // Collect the integer part of the number
      }
    }


    if (c == '.') {
      while (isdigit(s[++i] = c = getCh())) {
        // Collect the fraction part of the number
      }
    }

    s[i] = '\0';

    if (c != EOF) {
      ungetCh(c);
    }

    return NUMBER; // Flag the calling method that a number has been read into the stack
  }

  /* Get the last character pushed to the input buffer */
  int getCh(void) {
    return (bufferPos > 0) ? buff[--bufferPos] : getchar();
  }

  /* Push a character back to the input buffer */
  void ungetCh(int c) {
    if (bufferPos > BUFFSIZE) {
      printf("%s\n", "ungetCh(): too many characters");
    }
    else {
      buff[bufferPos++] = c;
    }
  }
