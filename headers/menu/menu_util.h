#ifndef MENU_UTIL_H_INCLUDED
#define MENU_UTIL_H_INCLUDED

#include "read_util.h"
#include <stdio.h>

#define BACK_TO_MAIN (DBL_MAX - 3.0)

/*Main menu for user interaction (which operation type should be run). Returns value A / B / C associated to operation type or quits the program (Q).*/
char askOperationType();
/*Asks user for the number which should be encoded with call by reference. If it is a 2K-bit pattern, the pattern will be converted to double*/
void askNumber_encoding(double *number_encoding, int *FPAccuracy);
/*Supporting function to request the desired accuracy. Returns the desired accuracy.*/
int askFPAccuracy_encoding();
/*Supporting function to request the existing format of the number to encode. Returns the existing format.*/
int askinputFormat_encoding();
/*Asks user for the encoded bit pattern which should be decoded (call by reference).*/
void askPattern_decoding(char **patternToDecode, int *FPAccuracy);
/*Supporting function to request the existing accuracy. Returns the desired accuracy.*/
int askFPAccuracy_decoding();
/*Asks user for the number which should be used for the arithmetic operation (call by reference). If it is a 2K-bit pattern, the patterns will be converted to double*/
void askNumbers_arithmetic(double *number1_arithmetic, double *number2_arithmetic, int *FPAccuracy);
/*Asks user for the desired arithmetic operation (call by reference)*/
void askArithmeticOperation(double *arithmeticOperation);


#endif