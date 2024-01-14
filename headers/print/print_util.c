#include <stdio.h>
#include <stdlib.h>

#include "menu_util.h"
#include "read_util.h"

void printChoice(&outputFormat)
{
        switch(*outputFormat) {
                case 'A':
                        /*Aufruf printResult-Funktion*/
                        break;
                case 'B':
                        /*Aufruf printCalculations-Funktion*/
                        break;
                default:
                        printf("Error: Invalid user choice: %f (selection must be A / B).\n\n", *outputFormat);
                        return INVALID_INPUT;
        }
}
