#include <stdio.h>
#include <stdlib.h>

#include "menu_util.h"
#include "read_util.h"
#include "print_util.h"

int main(void)
{
        double number1, number2; /*Werte, die an Philipp übergeben werden (Codieren und Arithmetik)*/
        char *patternToDecode = NULL; /*Bitmuster das an Philipp übergeben wird (Decodieren)*/
        int operationType = 0; /*Hauptmenü*/
        double arithmeticOperation; /*User-Wahl, welche Rechenoperation durchgeführt werden soll (an Philipp übergeben)*/
        int FPAccuracy; /*kommt von STR*/
        
        /*Fiktive Rückgabewerte*/
        char encoded_pattern[] = {'0', '0', '1', '1', '1', '0', '0', '1', '0', '0', '1', '1', '1', '0', '0', '1', '0', '0', '1', '1', '1', '0', '0', '1', '0', '0', '1', '1', '1', '0', '0', '1'}; /*kommt von PKO*/
        double decoded_number = 1.589655; /*kommt von PKO*/
        double arithmetic_result = 987.123; /*kommt von PKO*/
        double rounding_error = 0.12; /*kommt von PKO*/
        
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
                        printf("Uebergebene Zahl (double) an Philipp: %f\n", number1);
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
                                printf("Uebergebenes Muster (char) an Philipp: %s\n", patternToDecode);
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
                        printf("Uebergebene Zahl 1 (double) an Philipp fuer Arithmetik: %f\n", number1);
                        printf("Uebergebene Zahl 2 (double) an Philipp fuer Arithmetik: %f\n", number2);
                        askArithmeticOperation(&arithmeticOperation);
                        if (arithmeticOperation == BACK_TO_MAIN) {
                                continue;
                        }
                        printf("Gewuenschte Arithmetik (uebergeben an Philipp): %c\n", (char)arithmeticOperation);
                        if (print_arithmetic(arithmetic_result, rounding_error) ==BACK_TO_MAIN) {
                                continue;
                        }
                        return 0;
                }
        }
        return 0;
}