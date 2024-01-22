#ifndef BITS_H_INCLUDED
#define BITS_H_INCLUDED

#define EPSILON 0.0000001
#define EXTENSION_ERROR -10
#define GENERAL_ERROR -9999
#define MAX_BINARY_LENGTH 64

#define ALLOCATION_ERROR_MESSAGE() printf("Fehlercode: -99\n");
#define EXTENSION_ERROR_MESSAGE() printf("Fehlercode: -10\n");
#define GENERAL_ERROR_MESSAGE() printf("Fehlercode: -9999\n");
#define INVALID_INPUT_MESSAGE() printf("Fehlercode: -5\n");
#define PRINT_BINARY(x)                          \
        for (i = 0; i <= MAX_BINARY_LENGTH; ++i) \
        {                                        \
                printf("%c", *(x + i));          \
        }

/*This function re-initializes a given bitfield with the binary represantation of 0.*/
void clear_bitfield(char *bitfield);
/*Converts a given decimal digit into a binary digit. The resulting binary digit will be written in the given bitfield. Also possible to save negative binary-number which will be coded in 2K.*/
void decimal_into_binary(double number, char *bitfield);
/*Converts a given binary digit into a decimal digit and returns the decimal value.*/
double binary_into_decimal(char *bitfield);
/*Initializes a bitfield for further calcukations. Returns a pointer and reserves memory in heap.*/
char *initialize_bitfield();
/*Calculates, if a given decimal number is exactly representable as a binary digit. Returns boolean value as result.*/
int exactly_representable(double number);
/*Selects all fractional places of a given bitfield. Returns a pointer. Cuts off al the unused bitplaces in the bitfield.*/
char *get_fraction(char *bitfield);
/*Returns a pointer on a reserved memory in heap which contains the number from bitfield without fractions. Cuts off al the unused bitplaces in the bitfield. Respects the pre-sign bit.*/
char *get_pre_decimal(char *bitfield);
/*Returns a pointer on a reserved memory in heap which contains the number from bitfield without fractions. Cuts off al the unused bitplaces in the bitfield. Does not respect the pre-sign bit.*/
char *get_pre_decimal_pure(char *bitfield);
/*Calculates the addition of two given bitfields. Returns the binary digit representing the addition of both bitfields.*/
char *add_bitfields(char *bitfield1, char *bitfield2);
/*Calculates the subtraction of two given bitfields. Returns the binary digit representing the subtraction of both bitfields.*/
char *sub_bitfields(char *bitfield1, char *bitfield2);

#endif