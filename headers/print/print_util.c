#include <stdio.h>
#include <stdlib.h>

#include "print_util.h"

double print_encoded(char encoded_pattern[], int FPAccuracy)
{
        double outputFormat = 0;
        int i;
        printf("How shall we represent the result?\n");
        printf("\tEnter 'A' for the results only.\n");
        printf("\tEnter 'B' for the step-by-step explanation and calculations.\n");
        printf("\tEnter 'Q' to go back to main menu.\n\n");
        outputFormat = read_menuChoice();
        if (outputFormat == BUFFER_ERROR) {
                printf("Buffer Error. EOF. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (outputFormat == INVALID_INPUT || outputFormat == 'C') {
                printf("Invalid Input. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (outputFormat == 'Q') {
                printf("Going back to main menu ...\n\n");
                return BACK_TO_MAIN;
        } else if (outputFormat == 'A') {
                printf("Your number encoded is: ");
                if (FPAccuracy == 'A') {
                        for (i = 0; i < 8; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                }
                else if (FPAccuracy == 'B') {
                        for (i = 0; i < 16; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                }
                else if (FPAccuracy == 'C') {
                        for (i = 0; i < 32; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                }
                printf("\n");
        } else if (outputFormat == 'B') {
                if (FPAccuracy == 'A') {
                        ACCURACY_MESSAGE();
                        printf("Your choice was: 8-bit (FP,5,8) --> n = 8, k = 5\n\n");
                        read_enter();                                
                        STANDARDIZATION_MESSAGE();
                        read_enter();
                        printf("The presign-bit is: %c\n", encoded_pattern[0]);
                        PRESIGN_MESSAGE();
                        read_enter();
                        Q_MESSAGE();
                        printf("In this case 'q' is: %i\n\n", (int)pow(2, (8-5-1))-1);
                        read_enter();
                        printf("The exponent is: ");
                        for (i = 1; i <= 3; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        CHARACTERISTIC_MESSAGE();
                        read_enter();
                        printf("The mantissa is: ");
                        for (i = 4; i <= 7; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        MANTISSA_MESSAGE();
                        read_enter();
                        printf("Composed your number encoded is: ");
                        for (i = 0; i < 8; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        printf("%c_", encoded_pattern[0]);
                        for (i = 1; i <= 3; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("_");
                        for (i = 4; i <= 7; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        printf("Work is done. Exiting the program.\n");
                        return 0;                        
                }
                else if (FPAccuracy == 'B') {
                        ACCURACY_MESSAGE();
                        printf("Your choice was: 16-bit (FP,11,16) --> n = 16, k = 11\n\n");
                        read_enter();                                
                        STANDARDIZATION_MESSAGE();
                        read_enter();
                        printf("The presign-bit is: %c\n", encoded_pattern[0]);
                        PRESIGN_MESSAGE();
                        read_enter();
                        Q_MESSAGE();
                        printf("In this case 'q' is: %i\n\n", (int)pow(2, (16-11-1))-1);
                        read_enter();
                        printf("The exponent is: ");
                        for (i = 1; i <= 5; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        CHARACTERISTIC_MESSAGE();
                        read_enter();
                        printf("The mantissa is: ");
                        for (i = 6; i <= 15; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        MANTISSA_MESSAGE();
                        read_enter();
                        printf("Composed your number encoded is: ");
                        for (i = 0; i < 16; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        printf("%c_", encoded_pattern[0]);
                        for (i = 1; i <= 5; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("_");
                        for (i = 6; i <= 15; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        printf("Work is done. Exiting the program.\n");
                        return 0;
                }
                else if (FPAccuracy == 'C') {
                        ACCURACY_MESSAGE();
                        printf("Your choice was: 32-bit (FP,24,32) --> n = 32, k = 24\n\n");
                        read_enter();                                
                        STANDARDIZATION_MESSAGE();
                        read_enter();
                        printf("The presign-bit is: %c\n", encoded_pattern[0]);
                        PRESIGN_MESSAGE();
                        read_enter();
                        Q_MESSAGE();
                        printf("In this case 'q' is: %i\n\n", (int)pow(2, (32-24-1))-1);
                        read_enter();
                        printf("The exponent is: ");
                        for (i = 1; i <= 8; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        CHARACTERISTIC_MESSAGE();
                        read_enter();
                        printf("The mantissa is: ");
                        for (i = 9; i <= 31; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        MANTISSA_MESSAGE();
                        read_enter();
                        printf("Composed your number encoded is: ");
                        for (i = 0; i < 32; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        printf("%c_", encoded_pattern[0]);
                        for (i = 1; i <= 8; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("_");
                        for (i = 9; i <= 31; i++) {
                                printf("%c", encoded_pattern[i]);
                        }
                        printf("\n");
                        printf("Work is done. Exiting the program.\n");
                        return 0;
                }
        }
        printf("Exiting program.\n");
        return 0;
}



double print_decoded(double decoded_number, int FPAccuracy, char patternToDecode[])
{
        double outputFormat = 0;
        int i;
        printf("How shall we represent the result?\n");
        printf("\tEnter 'A' for the results only.\n");
        printf("\tEnter 'B' for the step-by-step explanation and calculations.\n");
        printf("\tEnter 'Q' to go back to main menu.\n\n");
        outputFormat = read_menuChoice();
        if (outputFormat == BUFFER_ERROR) {
                printf("Buffer Error. EOF. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (outputFormat == INVALID_INPUT || outputFormat == 'C') {
                printf("Invalid Input. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (outputFormat == 'Q') {
                printf("Going back to main menu ...\n\n");
                return BACK_TO_MAIN;
        } else if (outputFormat == 'A') {
                printf("Your pattern decoded as a decimal number is %f: \n", decoded_number);
        } else if (outputFormat == 'B') {
                if (FPAccuracy == 'A') {
                        ACCURACY_MESSAGE_DECODING();
                        printf("Your choice was: 8-bit (FP,5,8) --> n = 8, k = 5\n\n");
                        read_enter();                                
                        STANDARDIZATION_MESSAGE();
                        read_enter();
                        EXPLAIN_PATTERN_MESSAGE();
                        read_enter();
                        printf("The presign-bit is: %c\n", patternToDecode[0]);
                        read_enter();
                        Q_MESSAGE();
                        printf("In this case 'q' is: %i\n\n", (int)pow(2, (8-5-1))-1);
                        read_enter();
                        printf("The exponent is: ");
                        for (i = 1; i <= 3; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        printf("The mantissa is: ");
                        for (i = 4; i <= 7; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        DECODING_PROCESS_MESSAGE();
                        printf("Composed your bit-pattern is: ");
                        printf("%c_", patternToDecode[0]);
                        for (i = 1; i <= 3; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("_");
                        for (i = 4; i <= 7; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        printf("Your pattern decoded as a decimal number is %f: \n", decoded_number);
                        printf("Work is done. Exiting the program.\n");
                        return 0;                        
                }
                else if (FPAccuracy == 'B') {
                        ACCURACY_MESSAGE_DECODING();
                        printf("Your choice was: 16-bit (FP,11,16) --> n = 16, k = 11\n\n");
                        read_enter();                                
                        STANDARDIZATION_MESSAGE();
                        read_enter();
                        EXPLAIN_PATTERN_MESSAGE();
                        read_enter();
                        printf("The presign-bit is: %c\n", patternToDecode[0]);
                        read_enter();
                        Q_MESSAGE();
                        printf("In this case 'q' is: %i\n\n", (int)pow(2, (16-11-1))-1);
                        read_enter();
                        printf("The exponent is: ");
                        for (i = 1; i <= 5; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        printf("The mantissa is: ");
                        for (i = 6; i <= 15; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        DECODING_PROCESS_MESSAGE();
                        printf("Composed your bit-pattern is: ");
                        printf("%c_", patternToDecode[0]);
                        for (i = 1; i <= 5; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("_");
                        for (i = 6; i <= 15; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        printf("Your pattern decoded as a decimal number is %f: \n", decoded_number);
                        printf("Work is done. Exiting the program.\n");
                        return 0; 
                }
                else if (FPAccuracy == 'C') {
                        ACCURACY_MESSAGE_DECODING();
                        printf("Your choice was: 32-bit (FP,24,32) --> n = 32, k = 24\n\n");
                        read_enter();                                
                        STANDARDIZATION_MESSAGE();
                        read_enter();
                        EXPLAIN_PATTERN_MESSAGE();
                        read_enter();
                        printf("The presign-bit is: %c\n", patternToDecode[0]);
                        read_enter();
                        Q_MESSAGE();
                        printf("In this case 'q' is: %i\n\n", (int)pow(2, (32-24-1))-1);
                        read_enter();
                        printf("The exponent is: ");
                        for (i = 1; i <= 8; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        printf("The mantissa is: ");
                        for (i = 9; i <= 31; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        DECODING_PROCESS_MESSAGE();
                        printf("Composed your bit-pattern is: ");
                        printf("%c_", patternToDecode[0]);
                        for (i = 1; i <= 8; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("_");
                        for (i = 9; i <= 31; i++) {
                                printf("%c", patternToDecode[i]);
                        }
                        printf("\n");
                        printf("Your pattern decoded as a decimal number is %f: \n", decoded_number);
                        printf("Work is done. Exiting the program.\n");
                        return 0;
                }
        }
        printf("Exiting program.\n");
        return 0;
}


double print_arithmetic(double arithmetic_result, double rounding_error)
{
        double details = 0;
        printf("The result of your desired arithmetic operation is: %f\n", arithmetic_result);
        printf("The rounding error is: %f\n", rounding_error);
        printf("Please note: This is the result considering the given encoding and desired accuracy.\n");
        printf("The accuracy depends on the bits used for the arithmetic.\n");
        printf("Do you want more information?\n");
        printf("\tEnter 'A' for more information.\n");
        printf("\tEnter 'Q' to go back to main menu.\n\n");
        details = read_menuChoice();
        if (details == BUFFER_ERROR) {
                printf("Buffer Error. EOF. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (details == INVALID_INPUT || details == 'B' || details == 'C') {
                printf("Invalid Input. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (details == 'Q') {
                printf("Going back to main menu ...\n\n");
                return BACK_TO_MAIN;
        } else if (details == 'A') {
                ARITHMETIC_WELCOME_MESSAGE();
                read_enter();
                ACCURACY_MESSAGE();
                read_enter();
                ROUNDINGERROR_MESSAGE();
                read_enter();
                STANDARDIZATION_MESSAGE();
                read_enter();
                PRESIGN_MESSAGE();
                read_enter();
                Q_MESSAGE();
                read_enter();
                CHARACTERISTIC_MESSAGE();
                read_enter();
                MANTISSA_MESSAGE();
                read_enter();
                ARITHMETIC_GOODBYE_MESSAGE()
        }
        printf("Do you want to go back to main menu?\n");
        printf("\tEnter 'Q' to go back to main menu.\n");
        printf("\tEnter 'A' to exit the programm.\n\n");
        details = read_menuChoice();
        if (details == BUFFER_ERROR) {
                printf("Buffer Error. EOF. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (details == INVALID_INPUT || details == 'B' || details == 'C') {
                printf("Invalid Input. Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (details == 'Q') {
                printf("Going back to main menu...\n\n");
                return BACK_TO_MAIN;
        } else if (details == 'A') {
                printf("Exiting the program ...\n\n");
                return 0;
        }
        printf("Exiting program after arithmetic.\n");
        return 0;
}