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

double read_zeropos_buff();
int flush_buff();
double read_decimalNumber(int FPAccuracy);
double read_BinaryPattern(int FPAccuracy);
double isValidNumber_encoding(double inputNumber, int FPAccuracy);
char *read_patternToDecode(int bits);

#endif