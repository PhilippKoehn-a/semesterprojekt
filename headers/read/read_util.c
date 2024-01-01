#include "read_util.h"

/*Lese Benutzerauswahl (Menüführung)*/
double read_zeropos_buff()
{
        int x, status;
        int c = '\0';
        status = scanf ("%i", &x);
        if (status == EOF) {
                return BUFFER_ERROR;
        }
        if (status == 0 || x < 0 || (c = getchar ()) != '\n') {
                if (c == EOF || !flush_buff ()) {
                        return BUFFER_ERROR;
                }
                return INVALID_INPUT;
        }
        return x;
}

/*Lese Dezimalzahl für Eingabefunktion und Arithmetik*/
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
                return 0;
        }
        return decimal;
}


/*Lese binäres Bitmuster für Eingabefunktion und Arithmetik und konvertiere in double*/
double read_BinaryPattern(int FPAccuracy)
{
        char bitpattern[100];
        int max_len = 100, i = 0, dotCount = 0, length, integerPart = 0, dotPosition = -1;
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
                return 0;
        }
        return binary;
}




/*Definitionsbereich je Codierung*/
double isValidNumber_encoding(double inputNumber, int FPAccuracy)
{
        double lowerBound, upperBound;

        switch(FPAccuracy) {
                case 1:
                        lowerBound = -2*pow(2, 3);
                        upperBound = 2*pow(2, 3);
                        break;
                case 2:
                        lowerBound = -2*pow(2, 15);
                        upperBound = 2*pow(2, 15);
                        break;
                case 3:
                        lowerBound = -2*pow(2, 127);
                        upperBound = 2*pow(2, 127);
                        break;
                default:
                        printf("Error: Invalid Accuracy input: %i (must be 1 / 2 / 3).\n\n", FPAccuracy);
                        return INVALID_INPUT;
        }
        if (inputNumber > lowerBound && inputNumber < upperBound) {
                return inputNumber;
        } else {
        /*Fehler wenn Defiitionsbereich überschritten*/        
                return NOT_IN_RANGE;
        }
}




/*Lese codiertes Bitmuster für Decodierung*/
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


/*Hilfsfunktion zum Puffer leeren*/
int flush_buff()
{
        int c;
        while ((c = getchar ()) != '\n' && c != EOF) {}
        return c != EOF ;
}