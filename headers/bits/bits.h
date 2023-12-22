#ifndef BITS_H_INCLUDED
#define BITS_H_INCLUDED

#define EXTENSION_ERROR -10
#define GENERAL_ERROR -9999
#define ALLOCATION_ERROR -99
#define INVALID_INPUT -5
#define MAX_BINARY_LENGTH 64

#define EXTENSION_ERROR_MESSAGE() printf("Fehlercode: -10\n");
#define GENERAL_ERROR_MESSAGE() printf("Fehlercode: -9999\n");
#define ALLOCATION_ERROR_MESSAGE() printf("Fehlercode: -99\n");
#define INVALID_INPUT_MESSAGE() printf("Fehlercode: -5\n");
#define PRINT_BINARY(x)                          \
        for (i = 0; i <= MAX_BINARY_LENGTH; ++i) \
        {                                        \
                printf("%c", *(x + i));          \
        }

/*This function re-initializes a given bitfield with the binary represantation of 0.*/
void clear_bitfield(char *bitfield);
/*Converts a given decimal digit into a binary digit. The resulting binary digit will be written in the given bitfield*/
void decimal_into_binary(double number, char *bitfield);
/*Converts a given binary digit into a decimal digit and returns the decimal value.*/
double binary_into_decimal(char *bitfield);
/*Initializes a bitfield for further calcukations. Returns a pointer and reserves memory in heap.*/
char *initialize_bitfield();
/*Calculates, if a given decimal number is exactly representable as a binary digit. Returns boolean value as result.*/
int exactly_representable(double number);
#endif