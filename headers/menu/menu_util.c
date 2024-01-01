#include "menu_util.h"
#include "read_util.h"

/*Optionen Hauptmenü*/
int askOperationType()
{
        int operationType;
        printf("Which operation do you want to run?\n");
        printf("\tEnter '1' for coding of a real number.\n");
        printf("\tEnter '2' for decoding of a coded bit-pattern.\n");
        printf("\tEnter '3' for arithmetic operations.\n");
        printf("\tEnter '0' to exit the programm.\n\n");
        operationType = read_zeropos_buff();
        while (operationType > 3 || operationType < 0) {
                printf("Input not valid. Please select one of the options:\n");
                printf("\tEnter '1' for coding of a real number.\n");
                printf("\tEnter '2' for decoding.\n");
                printf("\tEnter '3' for arithmetic operations.\n");
                printf("\tEnter '0' to exit the programm.\n\n");
                operationType = read_zeropos_buff();
        }
        return operationType;
}


/*Eingabefunktion Codierung*/
/*Funktion kann aktuell 0-Werte nicht codieren, da 0 für Rücksprung in Hauptmenü reserviert*/
void askNumber_encoding(double *number_encoding)
{
        int FPAccuracy, inputFormat_encoding;
        
        /*Frage nach gewünschter Codierungsgenauigkeit*/
        FPAccuracy = askFPAccuracy_encoding();
        if (FPAccuracy == 0) {
                printf("Going back to main menu ...\n\n");
                *number_encoding = 0;
                return;
        }
        
        /*Frage nach gewünschtem Eingabeformat*/
        inputFormat_encoding = askinputFormat_encoding();
        if (inputFormat_encoding == 0) {
                printf("Going back to main menu ...\n\n");
                *number_encoding = 0;
                return;
        }
        
        /*Eingabe reelle Zahl wenn Dezimal*/
        if (inputFormat_encoding == 1) {
                printf("Please enter the number you want to code as a decimal.\n");
                printf("Example: 1234.5678 (fixed point) _or_ 12.3e589 (floating).\n");
                printf("'0' not allowed.\n\n");
                *number_encoding = read_decimalNumber(FPAccuracy);
                if (*number_encoding == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number_encoding = 0;
                } else if (*number_encoding == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number_encoding = 0;
                }
        /*Eingabe reelle Zahl wenn in binärem Bitmuster - Achtung 2K!*/
        } else {
                printf("Please enter the number you want to code as a 2K binary bit-pattern (max. 100 positions).\n");
                printf("Example: '1111.11' for the 2K binary bit-pattern of -1.75.\n");
                printf("'0'-Pattern not allowed.\n\n");
                *number_encoding = read_BinaryPattern(FPAccuracy);
                if (*number_encoding == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number_encoding = 0;
                } else if (*number_encoding == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number_encoding = 0;
                }              
        }
}


/*Hilfsfunktion Codierungsgenauigkeit*/
int askFPAccuracy_encoding()
{
        int FPAccuracy;
        do {                 
                printf("Please choose desired coding accuracy:\n");
                printf("\tEnter '1' for 8 bit and accurate to 4 decimal places.\n");
                printf("\tEnter '2' for 16 bit and accurate to 10 decimal places (IEEE binary16).\n");
                printf("\tEnter '3' for 32 bit and accurate to 23 decimal places (IEEE binary32).\n");
                printf("\tEnter '0' to go back to main menu.\n\n");
                FPAccuracy = read_zeropos_buff();
                if (FPAccuracy == 0) {
                        return FPAccuracy;
                } else if (FPAccuracy < 1 || FPAccuracy > 3) {
                        printf("Input not valid.\n\n");
                }
        } while (FPAccuracy < 1 || FPAccuracy > 3);
        return FPAccuracy;
}


/*Hilfsfunktion Eingabeformat*/
int askinputFormat_encoding()
{
        int inputFormat_encoding;

        do {
                printf("In which format is your real number?\n");
                printf("\tEnter '1' for decimal number (floating or fixed point).\n");
                printf("\tEnter '2' for bit pattern.\n");
                printf("\tEnter '0' to go back to main menu.\n\n");
                inputFormat_encoding = read_zeropos_buff();
                if (inputFormat_encoding == 0) {
                        return inputFormat_encoding;
                } else if (inputFormat_encoding < 1 || inputFormat_encoding > 2) {
                        printf("Input not valid.\n\n");
                }      
        } while (inputFormat_encoding < 1 ||inputFormat_encoding > 2);
        return inputFormat_encoding;
}


/*Eingabefunktion Decodierung*/
void askPattern_decoding(char **patternToDecode)
{
        int FPAccuracy = 0, bits = 0;
        /*Frage nach vorliegender Codierungsgenauigkeit*/
        FPAccuracy = askFPAccuracy_decoding();
        if (FPAccuracy == 0) {
                printf("Going back to main menu ...\n\n");
                return;
        }
        switch(FPAccuracy) {
                case 1:
                        bits = 8;
                        break;
                case 2:
                        bits = 16;
                        break;
                case 3:
                        bits = 32;
                        break;
                default:
                        printf("Error: Invalid Accuracy input: %i (must be 1 / 2 / 3).\n\n", FPAccuracy);
                        return;
        }
        printf("Please enter the number you want to decode with %i bits.\n\n", bits);
        *patternToDecode = read_patternToDecode(bits);
}



/*Hilfsfunktion Codierungsgenauigkeit*/
int askFPAccuracy_decoding()
{
        int FPAccuracy;
        do {
                printf("In which format is your coded number?\n");
                printf("\tEnter '1' for 8 bit.\n");
                printf("\tEnter '2' for 16 bit (IEEE binary16).\n");
                printf("\tEnter '3' for 32 bit (IEEE binary32).\n");
                printf("\tEnter '0' to go back to main menu.\n\n");
                FPAccuracy = read_zeropos_buff();
                if (FPAccuracy == 0) {
                        return FPAccuracy;
                } else if (FPAccuracy < 1 || FPAccuracy > 3) {
                        printf("Input not valid.\n\n");
                }
        } while (FPAccuracy < 1 ||FPAccuracy > 3);
        return FPAccuracy;
}



/*Eingabefunktion Arithmetik*/
void askNumbers_arithmetic(double *number1_arithmetic, double *number2_arithmetic)
{
        int FPAccuracy, inputFormat_encoding;
        
        FPAccuracy = askFPAccuracy_encoding();
        if (FPAccuracy == 0) {
                printf("Going back to main menu ...\n\n");
                *number1_arithmetic = 0;
                *number2_arithmetic = 0;
                return;
        }
        
        inputFormat_encoding = askinputFormat_encoding();
        if (inputFormat_encoding == 0) {
                printf("Going back to main menu ...\n\n");
                *number1_arithmetic = 0;
                *number2_arithmetic = 0;
                return;
        }
        
        if (inputFormat_encoding == 1) {
                printf("Please enter number 1 for your arithmetic as a decimal.\n");
                printf("Example: 1234.5678 (fixed point) _or_ 12.3e589 (floating).\n");
                printf("'0' not allowed.\n\n");
                *number1_arithmetic = read_decimalNumber(FPAccuracy);
                if (*number1_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number1_arithmetic = 0;
                        return;
                } else if (*number1_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number1_arithmetic = 0;
                        return;
                }
                printf("Please enter number 2 for your arithmetic as a decimal.\n");
                printf("Example: 1234.5678 (fixed point) _or_ 12.3e589 (floating).\n");
                printf("'0' not allowed.\n\n");
                *number2_arithmetic = read_decimalNumber(FPAccuracy);
                if (*number2_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number2_arithmetic = 0;
                        return;
                } else if (*number2_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number2_arithmetic = 0;
                        return;
                }
        } else {
                printf("Please enter number 1 for your arithmetic as a 2K binary bit-pattern (max. 100 positions).\n");
                printf("Example: '1111.11' for the 2K binary bit-pattern of -1.75.\n");
                printf("'0'-Pattern not allowed.\n\n");
                *number1_arithmetic = read_BinaryPattern(FPAccuracy);
                if (*number1_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number1_arithmetic = 0;
                        return;
                } else if (*number1_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number1_arithmetic = 0;
                        return;
                }
                printf("Please enter number2  for your arithmetic as a 2K binary bit-pattern (max. 100 positions).\n");
                printf("Example: '1111.11' for the 2K binary bit-pattern of -1.75.\n");
                printf("'0'-Pattern not allowed.\n\n");
                *number2_arithmetic = read_BinaryPattern(FPAccuracy);
                if (*number2_arithmetic == BUFFER_ERROR) {
                        printf("Buffer Error. EOF. Going back to main menu...\n\n");
                        *number2_arithmetic = 0;
                        return;
                } else if (*number2_arithmetic == INVALID_INPUT) {
                        printf("Invalid Input. Going back to main menu...\n\n");
                        *number2_arithmetic = 0;
                        return;
                }
        }
}