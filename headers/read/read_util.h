#ifndef READ_UTIL_H_INCLUDED
#define READ_UTIL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define VALID_INPUT 1
#define BUFFER_ERROR DBL_MAX
#define INVALID_INPUT (DBL_MAX - 1.0)
#define NOT_IN_RANGE (DBL_MAX - 2.0)
#define BACK_TO_MAIN (DBL_MAX - 3.0)


/*Basic function to interact with user*/
double read_menuChoice();
/*Reads decimal number for encoding and arithmetic. Checks if pattern fits into desired accuracy. Returns number to encode.*/
double read_decimalNumber(int FPAccuracy);
/*Reads 2K-binary pattern for encoding and arithmetic. Checks if pattern fits into desired accuracy. Returns number to encode.*/
double read_BinaryPattern(int FPAccuracy);
/*Support function for read_functions to check if given number can be represented in desired accuracy.*/
double isValidNumber_encoding(double inputNumber, int FPAccuracy);
/*Reads encoded pattern for decoding. Returns array with pattern.*/
char *read_patternToDecode(int bits);
/*Support function for read_functions to flush buffer.*/
int flush_buff();
/*Wait for user input*/
void read_enter();

#endif