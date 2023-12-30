#ifndef ARITHMETIC_H_INCLUDED
#define ARITHMETIC_H_INCLUDED

#define INVALID_CALL() printf("Der Funktionaufruf war ungueltig.\n");

/*Adds two given numbers (x + y) concerning a floating point encoding. User has to describe the floating point encoding which should be used.Returns the calculated value. If the calculation is not possible, 0 will be returned.*/
double add_floating_point(double x, double y, int mantissa_pre_sign);
/*Subtracts two given numbers (x - y) concerning a floating point encoding. User has to describe the floating point encoding which should be used.Returns the calculated value. If the calculation is not possible, 0 will be returned.*/
double sub_floating_point(double x, double y, int mantissa_pre_sign);

#endif