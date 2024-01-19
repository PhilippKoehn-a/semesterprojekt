#ifndef PRINT_UTIL_H_INCLUDED
#define PRINT_UTIL_H_INCLUDED

#include "read_util.h"
#include "menu_util.h"
#include <stdio.h>
#include <math.h>


#define BACK_TO_MAIN (DBL_MAX - 3.0)


#define ACCURACY_MESSAGE() \
        printf("The floating-point encoding is mainly limited by your desired accuracy.\n" \
        "We also call it the 'FP,k,n'-encoding:\n"\
        "\t- n: represents the bits, i.e. the 'length' of the bit-pattern\n"\
        "\t- k: affects the size of encoded decimal places\n"\
        "You will learn more about 'n' and 'k' in the following steps.\n");

#define STANDARDIZATION_MESSAGE() \
        printf("First your given number will be standardized to the format 'r = m*2^e':\n"\
        "\t- r is the real number standardized\n"\
        "\t- m is the mantissa with a value of 1<=m<2 2\n"\
        "\t- e is the exponent (also called characteristic).\n"\
        "The encoded number consists of a presign-bit, the exponent-bits and the mantissa-bits.\n\n");

#define PRESIGN_MESSAGE() \
        printf("If your given number is positive, the presign will be represented by '0' - else the presign is '1'.\n"\
        "This is the FIRST position in the encoded bit-pattern.\n\n")

#define Q_MESSAGE() \
        printf("We use the EX-q coding in (n-k) bits for the exponent.\n"\
        "So to calculate the characteristic we need 'q' which is calculated by the formula 'q = (2^(n-k-1))-1'\n"\
        "This formula ensures that approximately the same number of negative and positive exponents\n"\
        "can be encoded. So your given encoding-accuracy defines the q-value.\n\n");

#define CHARACTERISTIC_MESSAGE() \
        printf("We represent the exponent with (n-k) bits with the EX-q coding:\n"\
        "\t- use 'q' and add the integer-value of your standardized exponent\n"\
        "\t- encode result to binary bit pattern.\n"\
        "The bits of the characteristic are the MIDDLE positions of your encoded number.\n\n");

#define MANTISSA_MESSAGE() \
        printf("We represent the mantissa with (k-1) bits. \n"\
        "We don't encode pre-decimals (it is constantly '1'):\n"\
        "\t- mulitply decimals of stand. mantissa with 'm*2^(k-1)\n"\
        "\t- round it to next integer\n"\
        "\t- encode result to binary bit pattern\n"\
        "The bits of the mantissa are the LAST positions of your encoded number.\n\n");

#define ACCURACY_MESSAGE_DECODING() \
        printf("The length of your encoded bit-pattern is important for decoding.\n" \
        "We also call the bit-pattern, the 'FP,k,n'-encoding:\n"\
        "\t- n: represents the bits, i.e. the 'length' of the bit-pattern\n"\
        "\t- k: gives information about the encoded decimal places\n"\
        "You will learn more about 'n' and 'k' in the following steps.\n"\
        "Your bit-pattern was: ");

#define EXPLAIN_PATTERN_MESSAGE() \
        printf("Here are some further explanations\n"\
        "\t- the presign-bit represents negative (1) or positive numbers (0)\n"\
        "\t- the characteristic-bits [(n-k)-bits] follow the presign-bit and represent the exponent\n"\
        "\t- the mantissa-bits [(k-1)-bits] follow the exponent and represent the decimals of the mantissa\n\n");

#define DECODING_PROCESS_MESSAGE() \
        printf("And with all of this knowledge we can decode your pattern:\n"\
        "\t- with the presign-bit we know if it is a negative or positive number\n"\
        "\t- decode the exponent-bit-pattern and subtract 'q' to get the exponent\n"\
        "\t- decode the mantissa-bit-pattern and add '+1' to get the complete mantissa\n"\
        "\t- having the standardized format we just do simple maths to get a floating-point number\n\n");

#define ARITHMETIC_WELCOME_MESSAGE() \
        printf("To understand the arithmetic with encoded numbers,\n"\
        "firstly you should understand how the basic encoding works.\n"\
        "But no worries. In the next 10 minutes we'll teach you...\n\n");


#define ARITHMETIC_GOODBYE_MESSAGE() \
        printf("To understand the process more detailed, you can go back to the main menu.\n"\
        "There are many options available to learn more about the relation between\n"\
        "accuracy and encoding.\n\n");


double print_encoded(char encoded_pattern[], int FPAccuracy);
double print_decoded(double decoded_number, int FPAccuracy, char patternToDecode[]);
double print_arithmetic(double arithmetic_result);



#endif