#include "encode.h"
#include "decode.h"
#include "bits.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *exzess_q(int number, int bits)
{
        int q, i;
        char *encoding = malloc(bits * sizeof(char));

        if (encoding == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }
        q = pow(2, bits - 1) - 1;
        number = number + q;
        for (i = 0; i < bits; ++i)
        {

                if ((int)number % 2 == 0 && (int)number == 0)
                {
                        *(encoding + bits - 1 - i) = '0';
                        continue;
                }
                else if ((int)number % 2 == 0)
                {
                        *(encoding + bits - 1 - i) = '0';
                        number = (int)number / 2;
                        continue;
                }
                else if ((int)number % 2 == 1)
                {
                        *(encoding + bits - 1 - i) = '1';
                        number = (int)number / 2;
                        continue;
                }
        }

        return encoding;
}

char *fixed_point(double number, int after_coma, int bits)
{
        char *a = malloc(bits * sizeof(char));
        int i;

        if (a == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }

        number = number * pow(2, after_coma);
        if (number - floor(number) >= 0.5)
        {
                number = (int)number + 1;
        }
        else
        {
                number = floor(number);
        }
        for (i = 0; i < bits; ++i)
        {

                if ((int)number % 2 == 0 && (int)number == 0)
                {
                        *(a + bits - 1 - i) = '0';
                        continue;
                }
                else if ((int)number % 2 == 0)
                {
                        *(a + bits - 1 - i) = '0';
                        number = (int)number / 2;
                        continue;
                }
                else if ((int)number % 2 == 1)
                {
                        *(a + bits - 1 - i) = '1';
                        number = (int)number / 2;
                        continue;
                }
        }
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
                        while (number < 1)
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
char *floating_point(double number, int mantissa_pre_sign, int bits)
{
        char *encoding;
        char *encoded_exponent;
        char *encoded_mantissa;
        double mantissa;
        int exponent, i;
        encoding = malloc(bits * sizeof(char));
        if (encoding == NULL)
        {
                ALLOCATION_ERROR_MESSAGE();
                return NULL;
        }

        if (number > 0)
        {
                *(encoding) = '0';
        }
        else
        {
                *(encoding) = '1';
                number = number * -1;
        }
        exponent = standardize_floating_point(number, &mantissa);
        mantissa = mantissa - 1;

        encoded_exponent = exzess_q(exponent, bits - mantissa_pre_sign);
        for (i = 0; i < bits - mantissa_pre_sign; ++i)
        {
                *(encoding + 1 + i) = *(encoded_exponent + i);
        }
        if (bits == 8 && mantissa_pre_sign == 5)
        {
                if (number < MINIMUM_GK_5_8 || number > MAXIMUM_GK_5_8)
                {
                        OUT_OF_RANGE_ERROR_MESSAGE();
                        return NULL;
                }
                encoded_mantissa = fixed_point(mantissa, 4, 4);
                for (i = 0; i < 4; ++i)
                {
                        *(encoding + 4 + i) = *(encoded_mantissa + i);
                }
        }
        else if (bits == 16 && mantissa_pre_sign == 11)
        {

                if (number < MINIMUM_GK_11_16 || number > MAXIMUM_GK_11_16)
                {
                        OUT_OF_RANGE_ERROR_MESSAGE();
                        return NULL;
                }
                encoded_mantissa = fixed_point(mantissa, 10, 10);

                for (i = 0; i < 10; ++i)
                {
                        *(encoding + 6 + i) = *(encoded_mantissa + i);
                }
        }
        else if (bits == 32 && mantissa_pre_sign == 24)
        {
                if (number < MINIMUM_GK_24_32 || number > MAXIMUM_GK_24_32)
                {
                        OUT_OF_RANGE_ERROR_MESSAGE();
                        return NULL;
                }
                encoded_mantissa = fixed_point(mantissa, 23, 23);
                for (i = 0; i < 23; ++i)
                {
                        *(encoding + 9 + i) = *(encoded_mantissa + i);
                }
        }
        else
        {
                FALSE_VALUE_MESSAGE();
                return NULL;
        }

        free(encoded_mantissa);
        free(encoded_exponent);
        return encoding;
}

int calculate_exponent(double number)
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
                        while (number < 1)
                        {
                                number = number * 2;
                                --exponent;
                        }
                        return exponent;
                }
        }
        }
        return 0;
}
