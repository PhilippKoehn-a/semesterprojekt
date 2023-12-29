#ifndef ENCODE_H_INCLUDED
#define ENCODE_H_INCLUDED

#define FALSE_VALUE -3
#define MISSING_BIT_ERROR -2
#define MAXIMUM_GK_5_8 (2 * pow(2, 3))
#define MINIMUM_GK_5_8 (-2 * pow(2, 3))
#define MAXIMUM_GK_11_16 (2 * pow(2, 15))
#define MINIMUM_GK_11_16 (-2 * pow(2, 15))
#define MAXIMUM_GK_24_32 (2 * pow(2, 127))
#define MINIMUM_GK_24_32 (-2 * pow(2, -127))

#define OUT_OF_RANGE_ERROR_MESSAGE() printf("Die zu codierende Ziffer ist mit der bereitgestellten Codierungsvariante nicht codierbar.\n");
#define MISSING_BIT_ERROR_MESSAGE() printf("Nicht genug Bits zur Codierung bereitgestellt!\nFehlercode: -2\n");
#define FALSE_VALUE_MESSAGE() printf("Fehlerhafter Wert an Funktion vermittelt!\nFehlercode: -3\n");

/*Calculates the exzess-q encoding for a given number. User also has to set the amount of bits which could be used. Returns a pointer which reserves memory in heap and points at the encoded value. Returns a NULL pointer if the encoding is not possible with the given amount of bits.*/
char *exzess_q(int number, int bits);
/*Calculates the fixed-point-encoding for a given number.  User also has to set the amount of bits which could be used. Returns a pointer which reserves memory in heap and points at the encoded value. Returns a NULL pointer if the encoding is not possible with the given amount of bits. */
char *fixed_point(double number, int after_coma, int bits);
/*Standardizes a given floating point number. Saves the calculated mantissa value in the given double variable and returns the exponent.*/
int standardize_floating_point(double number, double *mantissa);
/*Calculates the floating point encoding of a given number with use of the given bits and mantissa digits. Returns a char pointer pointing at the resulting encoding in reserved heap-memory. Returns NULL if the encoding was unsuccesfull.*/
char *floating_point(double number, int mantissa_pre_sign, int bits);
/*Calcuates the exponent of a number in standardized floating point representation. Returns the exponent. Does not deliver mantissa values.*/
int calculate_exponent(double number);

#endif