#include "menu_util.h"

char askOperationType()
{
        double result;
        char operationType;
        printf("Which operation do you want to run?\n");
        printf("\tEnter 'A' for encoding of a real number.\n");
        printf("\tEnter 'B' for decoding of a coded bit-pattern.\n");
        printf("\tEnter 'C' for arithmetic operations.\n");
        printf("\tEnter 'Q' to exit the programm.\n\n");
        result = read_menuChoice();
        while (result == BUFFER_ERROR || result == INVALID_INPUT) {
                printf("Input not valid. Please select one of the options:\n");
                printf("\tEnter 'A' for encoding of a real number.\n");
                printf("\tEnter 'B' for decoding.\n");
                printf("\tEnter 'C' for arithmetic operations.\n");
                printf("\tEnter 'Q' to exit the programm.\n\n");
                result = read_menuChoice();
        }
        operationType = (char)result;
        return operationType;
}


void askNumber_encoding(double *number_encoding, int *FPAccuracy)
{
        int inputFormat_encoding;
        
        /*Frage nach gewünschter Codierungsgenauigkeit*/
        *FPAccuracy = askFPAccuracy_encoding();
        if (*FPAccuracy == 'Q') {
                printf("Going back to main menu ...\n\n");
                *number_encoding = BACK_TO_MAIN;
                return;
        }
        
        /*Frage nach gewünschtem Eingabeformat*/
        inputFormat_encoding = askinputFormat_encoding();
        if (inputFormat_encoding == 'Q') {
                printf("Going back to main menu ...\n\n");
                *number_encoding = BACK_TO_MAIN;
                return;
        }
        
        /*Eingabe reelle Zahl wenn Dezimal*/
        if (inputFormat_encoding == 'A' || inputFormat_encoding == 'B') {
                printf("Please enter the number you want to code as a decimal.\n");
                printf("Example: 1234.5678 (fixed point) _or_ 12.3e589 (floating).\n");
                *number_encoding = read_decimalNumber(*FPAccuracy);
                if (*number_encoding == BACK_TO_MAIN) {
                        return;
                }
                if (*number_encoding == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number_encoding = BACK_TO_MAIN;
                        return;
                } else if (*number_encoding == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number_encoding = BACK_TO_MAIN;
                        return;
                }
        /*Eingabe reelle Zahl wenn in binärem Bitmuster - Achtung 2K!*/
        } else if (inputFormat_encoding == 'C') {
                printf("Please enter the number you want to code as a 2K binary bit-pattern (max. 65 positions).\n");
                printf("Example: '1111.11' for the 2K binary bit-pattern of -1.75.\n");
                *number_encoding = read_BinaryPattern(*FPAccuracy);
                if (*number_encoding == BACK_TO_MAIN) {
                        return;
                }
                if (*number_encoding == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number_encoding = BACK_TO_MAIN;
                        return;
                } else if (*number_encoding == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number_encoding = BACK_TO_MAIN;
                        return;
                }              
        }
}


int askFPAccuracy_encoding()
{
        int FPAccuracy;
        do {                 
                printf("Please choose desired coding accuracy:\n");
                printf("\tEnter 'A' for 8 bit and accurate to 4 decimal places.\n");
                printf("\tEnter 'B' for 16 bit and accurate to 10 decimal places (IEEE binary16).\n");
                printf("\tEnter 'C' for 32 bit and accurate to 23 decimal places (IEEE binary32).\n");
                printf("\tEnter 'Q' to go back to main menu.\n\n");
                FPAccuracy = read_menuChoice();
                if (FPAccuracy == 'Q') {
                        return FPAccuracy;
                } else if (FPAccuracy == BUFFER_ERROR || FPAccuracy == INVALID_INPUT || (FPAccuracy != 'A' && FPAccuracy != 'B' && FPAccuracy != 'C')) {
                        printf("Input not valid.\n\n");
                }
        } while (FPAccuracy == BUFFER_ERROR || FPAccuracy == INVALID_INPUT || (FPAccuracy != 'A' && FPAccuracy != 'B' && FPAccuracy != 'C'));
        return FPAccuracy;
}


int askinputFormat_encoding()
{
        int inputFormat_encoding;

        do {
                printf("In which format is your real number?\n");
                printf("\tEnter 'A' for decimal number (fixed point).\n");
                printf("\tEnter 'B' for decimal number (floating).\n");
                printf("\tEnter 'C' for bit pattern.\n");
                printf("\tEnter 'Q' to go back to main menu.\n\n");
                inputFormat_encoding = read_menuChoice();
                if (inputFormat_encoding == 'Q') {
                        return inputFormat_encoding;
                } else if (inputFormat_encoding == BUFFER_ERROR || inputFormat_encoding == INVALID_INPUT || (inputFormat_encoding != 'A' && inputFormat_encoding != 'B' && inputFormat_encoding != 'C')) {
                        printf("Input not valid.\n\n");
                }      
        } while (inputFormat_encoding == BUFFER_ERROR || inputFormat_encoding == INVALID_INPUT || (inputFormat_encoding != 'A' && inputFormat_encoding != 'B' && inputFormat_encoding != 'C'));
        return inputFormat_encoding;
}


void askPattern_decoding(char **patternToDecode, int *FPAccuracy)
{
        int bits = 0;
        /*Frage nach vorliegender Codierungsgenauigkeit*/
        *FPAccuracy = askFPAccuracy_decoding();
        if (*FPAccuracy == 'Q') {
                printf("Going back to main menu ...\n\n");
                return;
        }
        switch(*FPAccuracy) {
                case 'A':
                        bits = 8;
                        break;
                case 'B':
                        bits = 16;
                        break;
                case 'C':
                        bits = 32;
                        break;
                default:
                        printf("Error: Invalid accuracy input: %i (selection must be A / B / C).\n\n", *FPAccuracy);
                        return;
        }
        printf("Please enter the number you want to decode with %i bits.\n\n", bits);
        *patternToDecode = read_patternToDecode(bits);
}


int askFPAccuracy_decoding()
{
        int FPAccuracy;
        do {
                printf("In which format is your coded number?\n");
                printf("\tEnter 'A' for 8 bit.\n");
                printf("\tEnter 'B' for 16 bit (IEEE binary16).\n");
                printf("\tEnter 'C' for 32 bit (IEEE binary32).\n");
                printf("\tEnter 'Q' to go back to main menu.\n\n");
                FPAccuracy = read_menuChoice();
                if (FPAccuracy == 'Q') {
                        return FPAccuracy;
                } else if (FPAccuracy == BUFFER_ERROR || FPAccuracy == INVALID_INPUT || (FPAccuracy != 'A' && FPAccuracy != 'B' && FPAccuracy != 'C')) {
                        printf("Input not valid.\n\n");
                }
        } while (FPAccuracy == BUFFER_ERROR || FPAccuracy == INVALID_INPUT || (FPAccuracy != 'A' && FPAccuracy != 'B' && FPAccuracy != 'C'));
        return FPAccuracy;
}


void askNumbers_arithmetic(double *number1_arithmetic, double *number2_arithmetic, int *FPAccuracy)
{
        int inputFormat_encoding;
        
        *FPAccuracy = askFPAccuracy_encoding();
        if (*FPAccuracy == 'Q') {
                printf("Going back to main menu ...\n\n");
                *number1_arithmetic = BACK_TO_MAIN;
                *number2_arithmetic = BACK_TO_MAIN;
                return;
        }
        
        inputFormat_encoding = askinputFormat_encoding();
        if (inputFormat_encoding == 'Q') {
                printf("Going back to main menu ...\n\n");
                *number1_arithmetic = BACK_TO_MAIN;
                *number2_arithmetic = BACK_TO_MAIN;
                return;
        }
        
        if (inputFormat_encoding == 'A' || inputFormat_encoding == 'B') {
                printf("Please enter number 1 for your arithmetic as a decimal.\n");
                printf("Example: 1234.5678 (fixed point) _or_ 12.3e589 (floating).\n");
                *number1_arithmetic = read_decimalNumber(*FPAccuracy);
                if (*number1_arithmetic == BACK_TO_MAIN) {
                        return;
                }
                if (*number1_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number1_arithmetic = BACK_TO_MAIN;
                        return;
                } else if (*number1_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number1_arithmetic = BACK_TO_MAIN;
                        return;
                }
                printf("Please enter number 2 for your arithmetic as a decimal.\n");
                printf("Example: 1234.5678 (fixed point) _or_ 12.3e589 (floating).\n");
                *number2_arithmetic = read_decimalNumber(*FPAccuracy);
                if (*number2_arithmetic == BACK_TO_MAIN) {
                        return;
                }
                if (*number2_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number2_arithmetic = BACK_TO_MAIN;
                        return;
                } else if (*number2_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number2_arithmetic = BACK_TO_MAIN;
                        return;
                }
        } else {
                printf("Please enter number 1 for your arithmetic as a 2K binary bit-pattern (max. 65 positions).\n");
                printf("Example: '1111.11' for the 2K binary bit-pattern of -1.75.\n");
                *number1_arithmetic = read_BinaryPattern(*FPAccuracy);
                if (*number1_arithmetic == BACK_TO_MAIN) {
                        return;
                }
                if (*number1_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number1_arithmetic = BACK_TO_MAIN;
                        return;
                } else if (*number1_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number1_arithmetic = BACK_TO_MAIN;
                        return;
                }
                printf("Please enter number2  for your arithmetic as a 2K binary bit-pattern (max. 65 positions).\n");
                printf("Example: '1111.11' for the 2K binary bit-pattern of -1.75.\n");
                *number2_arithmetic = read_BinaryPattern(*FPAccuracy);
                if (*number2_arithmetic == BACK_TO_MAIN) {
                        return;
                }
                if (*number2_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number2_arithmetic = BACK_TO_MAIN;
                        return;
                } else if (*number2_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number2_arithmetic = BACK_TO_MAIN;
                        return;
                }
        }
}


void askArithmeticOperation(double *arithmeticOperation)
{
        printf("Which arithmetic operation do you want to run?\n");
        printf("\tEnter 'A' for addition.\n");
        printf("\tEnter 'B' for subtraction.\n");
        printf("\tEnter 'C' for multiplication.\n");
        printf("\tEnter 'Q' to go back to main menu.\n\n");
        *arithmeticOperation = read_menuChoice();
        if (*arithmeticOperation == BUFFER_ERROR) {
                printf("Buffer Error. EOF. Going back to main menu...\n\n");
                *arithmeticOperation = BACK_TO_MAIN;
                return;
        }
        else if (*arithmeticOperation == INVALID_INPUT) {
                printf("Invalid Input. Going back to main menu...\n\n");
                return;
        }
        else if (*arithmeticOperation == 'Q') {
                printf("Going back to main menu ...\n\n");
                *arithmeticOperation = BACK_TO_MAIN;
                return;
        } 
}