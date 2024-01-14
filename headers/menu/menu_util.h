#ifndef MENU_UTIL_H_INCLUDED
#define MENU_UTIL_H_INCLUDED

#include <stdio.h>

#define BACK_TO_MAIN (DBL_MAX - 3.0)

char askOperationType();
int askinputFormat_encoding();
int askFPAccuracy_encoding();
void askNumber_encoding(double *number_encoding);
int askFPAccuracy_decoding();
void askPattern_decoding(char **patternToDecode);
void askNumbers_arithmetic(double *number1_arithmetic, double *number2_arithmetic);
void askArithmeticOperation(double *arithmeticOperation);
void askOutputFormat(double *outputFormat);


#endif