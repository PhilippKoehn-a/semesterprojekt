#include "read_util.h"

double read_menuChoice()
{
        char menuChoice[2];
        int max_len = 2, i = 0;
        char c = getchar();
        while (c != '\n' && i < max_len - 1) {
                menuChoice[i++] = c;
                c = getchar();
        }
        if (i == max_len - 1 && c != '\n') {
                if (c == EOF || !flush_buff ()) {
                        return BUFFER_ERROR;
                }
                return INVALID_INPUT;
        }
        menuChoice[i] = '\0';
        if (menuChoice[0] != 'A' && menuChoice[0] != 'B' && menuChoice[0] != 'C' && menuChoice[0] != 'Q') {
                return INVALID_INPUT;
        }
        return (double)menuChoice[0];
}


double read_decimalNumber(int FPAccuracy)
{
        double decimal;
        int status;
        int c = '\0';
        status = scanf ("%lf", &decimal);
        if (status == EOF) {
                return BUFFER_ERROR;
        }
        if (status == 0 || (c = getchar ()) != '\n') {
                if (c == EOF || !flush_buff ()) {
                        return BUFFER_ERROR;
                }
                return INVALID_INPUT;
        }
        /*Fehler, wenn Zahl nicht in gewünschte Genauigkeit passt
        (ausserhalb des Definitionsbereichs der gewünschten Codierung)*/
        if (isValidNumber_encoding(decimal, FPAccuracy) == NOT_IN_RANGE) {
                printf("Input can't be represented in desired accuracy. Going back to main menu ...\n\n");
                decimal = BACK_TO_MAIN;
        }
        return decimal;
}


double read_BinaryPattern(int FPAccuracy)
{
        char bitpattern[66];
        int max_len = 65, i = 0, dotCount = 0, length, integerPart = 0, dotPosition = -1;
        double binary = 0.0, fractionPart = 0.0;
        char c = getchar();
        while (c != '\n' && i < max_len - 1) {
                bitpattern[i++] = c;
                c = getchar();
        }
        if (i == max_len - 1 && c != '\n') {
                if (c == EOF || !flush_buff ()) {
                        return BUFFER_ERROR;
                }
                return INVALID_INPUT;
        }
        bitpattern[i] = '\0';
        length = strlen(bitpattern);
        /*Prüfe, ob nur zulässige Zeichen eingegeben wurden(alle Zeichen, außer Nullterminierung)*/
        for (i = 0; i < length; i++) {
                if (bitpattern[i] != '0' && bitpattern[i] != '1' && bitpattern[i] != '.') {
                        return INVALID_INPUT;
        }
        /*Prüfe, ob maximal ein Punkt eingegeben wurde*/
                if (bitpattern[i] == '.') {
                        dotCount++;
                        if (dotCount > 1) {
                                return INVALID_INPUT;
                        }
                }
        }
        /*Umwandlung von string zu double*/
        /*Finde Komma*/
        for (i = 0; bitpattern[i] != '\0'; i++) {
                if (bitpattern[i] == '.') {
                        dotPosition = i;
                }
        }
        /*Konvertierein double, wenn Komma gefunden*/
        if (dotPosition != -1) {
                /*Berücksichtige Vorzeichen in 2K-Codierung*/
                if (bitpattern[0] == '1') {
                        integerPart = -(bitpattern[0] - '0')*pow(2, (dotPosition - 1));
                } else {
                        integerPart = (bitpattern[0] - '0')*pow(2, (dotPosition - 1));
                }
                /*Berechne Integer-Part*/
                for (i = 1; i < dotPosition; i++) {
                        integerPart += (bitpattern[i] - '0')*pow(2, (dotPosition - 1 - i));
                }
                /*Berechne Fraction-Part*/
                for (i = dotPosition + 1; bitpattern[i] != '\0'; i++) {
                        fractionPart += (bitpattern[i] - '0')*pow(2, -(i - dotPosition));
                }
                if (bitpattern[0] == '1') {
                        binary = integerPart - fractionPart;
                } else {
                        binary = integerPart + fractionPart;
                }
        /*Konvertiere in double, wenn kein Komma vorhanden*/
        } else {
                /*Berücksichtige Vorzeichen in 2K-Codierung*/
                if (bitpattern[0] == '1') {
                        binary = -(bitpattern[0] - '0')*pow(2, (strlen(bitpattern) - 1));
                } else {
                        binary = (bitpattern[0] - '0')*pow(2, (strlen(bitpattern) - 1));
                }
                /*Berechne Integer-Part*/
                for (i = 1; bitpattern[i] != '\0'; i++) {
                        binary += (bitpattern[i] - '0')*pow(2, (strlen(bitpattern)- 1 - i));
                }
        }
        /*Fehler, wenn Zahl nicht in gewünschte Genauigkeit passt
        (ausserhalb des Definitionsbereichs der gewünschten Codierung)*/
        if (isValidNumber_encoding(binary, FPAccuracy) == NOT_IN_RANGE) {
                printf("Input can't be represented in desired accuracy. Going back to main menu ...\n\n");
                return BACK_TO_MAIN;
        }
        return binary;
}


double isValidNumber_encoding(double inputNumber, int FPAccuracy)
{
        double lowerBound, upperBound;

        switch(FPAccuracy) {
                case 'A':
                        lowerBound = -2*pow(2, 3);
                        upperBound = 2*pow(2, 3);
                        break;
                case 'B':
                        lowerBound = -2*pow(2, 15);
                        upperBound = 2*pow(2, 15);
                        break;
                case 'C':
                        lowerBound = -2*pow(2, 127);
                        upperBound = 2*pow(2, 127);
                        break;
                default:
                        printf("Error: Invalid accuracy input: %i (selection must be A / B / C).\n\n", FPAccuracy);
                        return INVALID_INPUT;
        }
        if (inputNumber > lowerBound && inputNumber < upperBound) {
                return inputNumber;
        } else {
        /*Fehler wenn Definitionsbereich überschritten*/        
                return NOT_IN_RANGE;
        }
}


char *read_patternToDecode(int bits)
{
        char *patternToDecode = malloc((bits + 1) * sizeof(char));
        int j = 0, i = 0;
        char c = getchar();
        if (patternToDecode == NULL) {
                return NULL;
        }
        while (c != '\n' && i < bits) {
                patternToDecode[i++] = c;
                c = getchar();
        }
        if (i < bits) {
                printf("Too few bits entered! Back to main menu ...\n\n");
                free(patternToDecode);
                return NULL;
        }
        if (i == bits && c != '\n') {
                if (c == EOF || !flush_buff ()) {
                        free(patternToDecode);
                        return NULL;
                }
                printf("Too many bits entered! Back to main menu ...\n\n");
                free(patternToDecode);
                return NULL;
        }
        for (j = 0; j < bits; j++) {
                if (patternToDecode[j] != '0' && patternToDecode[j] != '1') {
                        free(patternToDecode);
                        return NULL;
                }
        }
        patternToDecode[i] = '\0';
        return patternToDecode;
}


int flush_buff()
{
        int c;
        while ((c = getchar ()) != '\n' && c != EOF) {}
        return c != EOF;
}


void read_enter()
{
        char c;
        printf("Press enter to proceed...\n\n");
        while ((c = getchar ()) != '\n') {}
}