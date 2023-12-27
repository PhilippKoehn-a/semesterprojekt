#include "encode.h"
#include "bits.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *exzess_q(int number, int bits)
{
        int q;
        char *p = initialize_bitfield();
        char *a;

        if (p == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }
        q = pow(2, bits - 1) - 1;
        number = number + q;
        decimal_into_binary(number, p);
        a = get_pre_decimal(p);
        if ((int)strlen(a) - 2 > bits)
        {
                MISSING_BIT_ERROR_MESSAGE();
                a = NULL;
                return a;
        }
        free(p);

        return a;
}

char *fixed_point(double number, int after_coma, int bits)
{
        int i;
        char *p = initialize_bitfield();
        char *a = malloc((bits) * sizeof(char));
        char *temp;

        if (number < 0)
        {
                FALSE_VALUE_MESSAGE();
                return NULL;
        }

        if (p == NULL || a == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }
        number = pow(2, after_coma) * number;
        if (number - floor(number) > 0.5)
        {
                number = (int)number + 1;
        }
        else
        {
                number = (int)number;
        }
        decimal_into_binary(number, p);
        temp = get_pre_decimal(p);
        if (temp == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }
        for (i = 0; i <= bits; ++i)
        {
                if (*(temp + i) == '1' || *(temp + i) == '0')
                {
                        *(a + i) = *(temp + i);
                }
                else
                {
                        break;
                }
        }
        for (i = 0; i < bits; ++i) /*re-sorting entries to eliminate pre-sign bit*/
        {
                *(a + i) = *(a + i + 1);
        }
        *(a + bits) = '\0';
        for (i = 0; i < bits; ++i)
        {
                if (*(a + i) != '0' && *(a + i) != '1')
                {
                        *(a + i) = '0';
                        for (i = 0; i < bits - 1; ++i) /*re-sorting entries if not all the bits were used */
                        {
                                *(a + bits - 1 - i) = *(a + bits - 2 - i);
                        }
                        *a = '0';
                }
        }
        if (binary_into_decimal(a) != number) /*check, if the encoding was possible with the given amount of bits*/
        {
                MISSING_BIT_ERROR_MESSAGE();
                return NULL;
        }

        free(temp);
        free(p);
        return a;
}

int standardize_floating_point(double number, double *mantissa)
{
        int exponent;
        exponent = 0;
        switch (number > 2)
        {
        case (1):
        {
                while (number >= 2)
                {
                        number = number / 2;
                        ++exponent;
                }
                *mantissa = number;
                return exponent;
        }
        case (0):
        {
                if (number < 0)
                {
                        FALSE_VALUE_MESSAGE();
                        return FALSE_VALUE;
                }
                else
                {
                        while (number <= 1)
                        {
                                number = number * 2;
                                --exponent;
                        }
                        *mantissa = number;
                        return exponent;
                }
        }
        }
        return 0;
}
