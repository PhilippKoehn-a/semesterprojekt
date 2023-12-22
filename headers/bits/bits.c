#include "bits.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void clear_bitfield(char *bitfield)
{
        int i;

        for (i = 0; i < MAX_BINARY_LENGTH; ++i)
        {
                if (i == 31)
                {
                        *(bitfield + i) = '.';
                }
                else
                {
                        *(bitfield + i) = '0';
                }
        }
}

void decimal_into_binary(double number, char *bitfield)
{
        int bytes, i, whole_number;
        double fraction;

        whole_number = (int)number;
        fraction = number - whole_number;
        bytes = sizeof(bitfield);

        if (whole_number > pow(2, bytes * 8) - 1 || whole_number > INT_MAX || whole_number < 0)
        {
                clear_bitfield(bitfield);
                EXTENSION_ERROR_MESSAGE();
        }

        for (i = 30; i >= 0; --i)
        {
                if (whole_number % 2 == 0 && whole_number == 0)
                {
                        *(bitfield + i) = '0';
                        continue;
                }
                else if (whole_number % 2 == 0)
                {
                        *(bitfield + i) = '0';
                        whole_number = whole_number / 2;
                        continue;
                }
                else if (whole_number % 2 == 1)
                {
                        *(bitfield + i) = '1';
                        whole_number = whole_number / 2;
                        continue;
                }
        }
        for (i = 33; i < MAX_BINARY_LENGTH; ++i)
        {
                if (fraction == 0)
                {
                        break;
                }
                else
                {
                        if (fraction * 2 >= 1)
                        {
                                *(bitfield + i) = '1';
                                fraction = fraction * 2 - 1;
                        }
                        else
                        {
                                *(bitfield + i) = '1';
                                fraction = fraction * 2;
                        }
                }
        }
}

double binary_into_decimal(char *bitfield)
{
        int i, fraction_counter, wholes_counter;
        double decimal;

        fraction_counter = 0;
        wholes_counter = 0;
        decimal = 0;

        for (i = MAX_BINARY_LENGTH / 2 - 2; i >= 0; --i)
        {
                decimal = decimal + (int)(*(bitfield + i) - 48) * pow(2, wholes_counter);
                ++wholes_counter;
        }
        for (i = MAX_BINARY_LENGTH / 2 + 1; i <= MAX_BINARY_LENGTH; ++i)
        {
                ++fraction_counter;
                decimal = decimal + (int)(*(bitfield + i) - 48) * (pow(0.5, fraction_counter));
        }

        return decimal;
}

char *initialize_bitfield()
{
        int i;
        char *p = malloc(MAX_BINARY_LENGTH * sizeof(char));
        if (p == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }
        for (i = 0; i < MAX_BINARY_LENGTH; ++i)
        {
                if (i == 31)
                {
                        *(p + i) = '.';
                }
                else
                {
                        *(p + i) = '0';
                }
        }
        *(p + MAX_BINARY_LENGTH) = '\0';

        return p;
}

int exactly_representable(double number)
{
        char *p = initialize_bitfield();
        double proof;
        decimal_into_binary(number, p);
        proof = binary_into_decimal(p);

        if (proof == number)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}
