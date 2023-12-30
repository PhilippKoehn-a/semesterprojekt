#include "bits.h"
#include "encode.h"
#include "decode.h"
#include "arithmetic.h"
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
        for (i = 32; i < MAX_BINARY_LENGTH; ++i)
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
                                *(bitfield + i) = '0';
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

        if (proof == number || proof - number < fabs(EPSILON))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

char *get_fraction(char *bitfield)
{
        char *p;
        int i, unused_bits;
        i = 0;
        unused_bits = 0;
        while (*(bitfield + MAX_BINARY_LENGTH - 1 - i) == '0')
        {
                ++i;
                ++unused_bits;
        }
        unused_bits = 32 - unused_bits;

        p = malloc(unused_bits * sizeof(char));
        if (p == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }

        for (i = 0; i < unused_bits; ++i)
        {
                *(p + i) = *(bitfield + 32 + i);
        }

        return p;
}

char *get_pre_decimal(char *bitfield)
{
        char *p;
        int i, unused_bits;
        unused_bits = 0;
        i = 0;
        while (*(bitfield) == '0')
        {
                ++bitfield;
                ++unused_bits;
        }
        --bitfield; /*respecting pre-sign bit*/
        unused_bits = 32 - unused_bits;

        p = malloc((unused_bits) * sizeof(char));
        if (p == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }

        bitfield = bitfield - unused_bits;

        for (i = 0; i < unused_bits; ++i)
        {
                if (*(bitfield + unused_bits + i) == '.')
                {
                        break;
                }
                else
                {
                        *(p + i) = *(bitfield + unused_bits + i);
                }
        }

        return p;
}

char *get_pre_decimal_pure(char *bitfield)
{
        char *p;
        int i, unused_bits;
        unused_bits = 0;
        i = 0;
        while (*(bitfield) == '0')
        {
                ++bitfield;
                ++unused_bits;
        }

        unused_bits = 32 - unused_bits;

        p = malloc((unused_bits) * sizeof(char));
        if (p == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }

        bitfield = bitfield - unused_bits;

        for (i = 0; i < unused_bits; ++i)
        {
                if (*(bitfield + unused_bits + i) == '.')
                {
                        break;
                }
                else
                {
                        *(p + i) = *(bitfield + unused_bits + i);
                }
        }

        return p;
}
char *add_bitfields(char *bitfield1, char *bitfield2)
{
        int i;
        char *result = initialize_bitfield();
        if (result == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }
        clear_bitfield(result);

        for (i = MAX_BINARY_LENGTH - 1; i >= 0; --i)
        {
                if (*(bitfield1 + i) == '.' || *(bitfield1 + i) == '\0')
                {
                        continue;
                }
                if ((((int)*(bitfield1 + i) - 48) + ((int)*(bitfield2 + i) - 48) + ((int)*(result + i) - 48)) % 2 == 0)
                {
                        if ((((int)*(bitfield1 + i) - 48) + ((int)*(bitfield2 + i) - 48) + ((int)*(result + i) - 48)) == 2)
                        {
                                if (i != 32)
                                {
                                        *(result + i - 1) = '1';
                                }
                                else
                                {
                                        *(result + i - 2) = '1';
                                }
                        }
                        *(result + i) = '0';
                }
                else if ((((int)*(bitfield1 + i) - 48) + ((int)*(bitfield2 + i) - 48) + ((int)*(result + i) - 48)) % 2 == 1)
                {

                        if ((((int)*(bitfield1 + i) - 48) + ((int)*(bitfield2 + i) - 48) + ((int)*(result + i) - 48)) > 2)
                        {
                                if (i != 32)
                                {
                                        *(result + i - 1) = '1';
                                }
                                else
                                {
                                        *(result + i - 2) = '1';
                                }
                        }
                        *(result + i) = '1';
                }
        }
        return result;
}