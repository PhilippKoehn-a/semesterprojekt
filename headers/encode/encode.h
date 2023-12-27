#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED

#define FALSE_VALUE -3
#define MISSING_BIT_ERROR -2
#define MISSING_BIT_ERROR_MESSAGE() printf("Nicht genug Bits zur Codierung bereitgestellt!\nFehlercode: -2\n");
#define FALSE_VALUE_MESSAGE() printf("Fehlerhafter Wert an Funktion vermittelt!!\nFehlercode: -3\n");

/*Calculates the exzess-q encoding for a given number. User also has to set the amount of bits which could be used. Returns a pointer which reserves memory in heap and points at the encoded value. Returns a NULL pointer if the encoding is not possible with the given amount of bits.*/
char *exzess_q(int number, int bits);
/*Calculates the fixed-point-encoding for a given number.  User also has to set the amount of bits which could be used. Returns a pointer which reserves memory in heap and points at the encoded value. Returns a NULL pointer if the encoding is not possible with the given amount of bits. */
char *fixed_point(double number, int after_coma, int bits);
/*Standardizes a given floating point number. Saves the calculated mantissa value in the given double variable and returns the exponent.*/
int standardize_floating_point(double number, double *mantissa);

#endif