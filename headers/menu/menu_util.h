#ifndef MENU_UTIL_H_INCLUDED
#define MENU_UTIL_H_INCLUDED

#include <stdio.h>

int askOperationType();
int askinputFormat_encoding();
int askFPAccuracy_encoding();
void askNumber_encoding(double *number_encoding);
int askFPAccuracy_decoding();
void askPattern_decoding(char **patternToDecode);
void askNumbers_arithmetic(double *number1_arithmetic, double *number2_arithmetic);

#endif