#include <stdio.h>
#include <stdlib.h>

#include "menu_util.h"
#include "read_util.h"
#include "print_util.h"
#include "arithmetic.h"
#include "bits.h"
#include "decode.h"
#include "encode.h"


int main(void)
{
        double number1, number2; /*Werte, die an Philipp übergeben werden (Codieren und Arithmetik)*/
        char *patternToDecode = NULL; /*Bitmuster das an Philipp übergeben wird (Decodieren)*/
        int operationType = 0; /*Hauptmenü*/
        double arithmeticOperation; /*User-Wahl, welche Rechenoperation durchgeführt werden soll (an Philipp übergeben)*/
        int FPAccuracy;
        int mantissa_pre_sign;
        int bits;
        
        /*Fiktive Rückgabewerte*/
        char *encoded_pattern;
        double decoded_number;
        double arithmetic_result;
        double rounding_error;
        
        /*Endlosschleife - laeuft so lange nicht 0 uebergeben wird*/
        printf("======================================================================================\n");
        printf("This program offers coding/decoding of real numbers with an accuracy of 8bit / 16bit / \n");
        printf("32bit and shows also the calculations. The program can also do some simple arithmetic\n"); 
        printf("operations (addition, subtraction).\n");
        printf("Have fun with the program and if you need any information check the read_me.txt\n");
        printf("====================================================================================\n\n");
        
        while(1)
        {
                /*Rufe Hauptmenü auf*/
                operationType = askOperationType();
                /*Programmabbruch bei Q*/
                if (operationType == 'Q') {
                        printf("Exiting the program...\n");
                        return 0;                
                /*Codieren*/
                } else if (operationType == 'A') {
                        askNumber_encoding(&number1, &FPAccuracy);
                        if (number1 == BACK_TO_MAIN) {
                                continue;
                        }
                        if (FPAccuracy == 'A') {
                                mantissa_pre_sign = 5;
                                bits = 8;
                        } else if (FPAccuracy == 'B') {
                                mantissa_pre_sign = 11;
                                bits = 16;
                        } else if (FPAccuracy == 'C') {
                                mantissa_pre_sign = 24;
                                bits = 32;
                        }
                        encoded_pattern = floating_point(number1, mantissa_pre_sign, bits);
                        if (print_encoded(encoded_pattern, FPAccuracy) == BACK_TO_MAIN) {
                                continue;
                        }
                        return 0;
                }
                /*Decodieren*/
                else if (operationType == 'B') {
                        askPattern_decoding(&patternToDecode, &FPAccuracy);
                        if (patternToDecode != NULL)
                        {
                                if (number1 == BACK_TO_MAIN) {
                                        continue;
                                }
                                if (FPAccuracy == 'A') {
                                        mantissa_pre_sign = 5;
                                        bits = 8;
                                } else if (FPAccuracy == 'B') {
                                        mantissa_pre_sign = 11;
                                        bits = 16;
                                } else if (FPAccuracy == 'C') {
                                        mantissa_pre_sign = 24;
                                        bits = 32;
                                }
                                decoded_number = decode_floating_point(patternToDecode, mantissa_pre_sign, bits);
                                if (print_decoded(decoded_number, FPAccuracy, patternToDecode) == BACK_TO_MAIN) {
                                        continue;
                                }
                                free(patternToDecode); /*Speicherreservierung auflösen*/
                                return 0;
                        }                        
                }
                /*Arithmetik*/
                else if (operationType == 'C') {
                        askNumbers_arithmetic(&number1, &number2, &FPAccuracy);
                        if (number1 == BACK_TO_MAIN || number2 == BACK_TO_MAIN) {
                                continue;
                        }
                        if (FPAccuracy == 'A') {
                                mantissa_pre_sign = 5;
                                bits = 8;
                        } else if (FPAccuracy == 'B') {
                                mantissa_pre_sign = 11;
                                bits = 16;
                        } else if (FPAccuracy == 'C') {
                                mantissa_pre_sign = 24;
                                bits = 32;
                        }                        
                        
                        
                        askArithmeticOperation(&arithmeticOperation);
                        if (arithmeticOperation == BACK_TO_MAIN) {
                                continue;
                        }
                        if (arithmeticOperation =='A') {
                                arithmetic_result = add_floating_point(number1, number2, mantissa_pre_sign);
                                rounding_error = rounding_error_decimal(number1, number2, '+', mantissa_pre_sign);

                        } else if (arithmeticOperation == 'B') {
                                arithmetic_result = sub_floating_point(number1, number2, mantissa_pre_sign);
                                rounding_error = rounding_error_decimal(number1, number2, '-', mantissa_pre_sign);
                        }
                        if (print_arithmetic(arithmetic_result, rounding_error) ==BACK_TO_MAIN) {
                                continue;
                        }
                        return 0;
                }
        }
        return 0;
}