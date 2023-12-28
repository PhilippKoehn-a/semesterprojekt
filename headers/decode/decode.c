#include "bits.h"
#include "encode.h"
#include "decode.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double decode_exzess_q(char *encoding, int q)
{
        double decode;
        char *temp;
        int i, digits, power;
        digits = 0;
        i = 0;
        power = 0;

        while (*(encoding + i) == '0' || *(encoding + i) == '1')
        {
                ++digits;
                ++i;
        }
        temp = malloc(digits * sizeof(char));
        for (i = 0; i < digits; ++i)
        {
                *(temp + i) = *(encoding + i);
        }
        for (i = digits - 1; i >= 0; --i)
        {
                decode = decode + (int)(*(encoding + i) - 48) * pow(2, power);
                ++power;
        }
        decode = decode - q;
        free(temp);
        return decode;
}

double decode_fixed_point(char *encoding, int after_coma)
{
        int digits, i;
        int power = 0;
        double decode = 0;
        digits = 0;
        i = 0;
        while (*(encoding + i) == '0' || *(encoding + i) == '1')
        {
                ++digits;
                ++i;
        }
        while (digits != 0)
        {
                decode = decode + (int)(*(encoding + digits - 1) - 48) * pow(2, power);
                ++power;
                --digits;
        }

        decode = decode / pow(2, after_coma);
        return decode;
}
double decode_floating_point(char *encoding, int mantissa_pre_sign, int bits)
{
        char *mantissa;
        char *exponent;
        double decode;
        double decoded_exponent;
        double decoded_mantissa;
        int i;

        if (bits == 8 && mantissa_pre_sign == 5)
        {
                mantissa = malloc(4 * sizeof(char));
                exponent = malloc(3 * sizeof(char));
                if (mantissa == NULL || exponent == NULL)
                {
                        ALLOCATION_ERROR_MESSAGE();
                        return ALLOCATION_ERROR;
                }
                for (i = 0; i < 4; ++i)
                {
                        *(mantissa + 3 - i) = *(encoding + 7 - i);
                }
                printf("\nDie codierte  Mantisse: ");
                for (i = 0; i < 4; ++i)
                {
                        printf("%c", *(mantissa + i));
                }
                printf("\n");
                for (i = 0; i < 3; ++i)
                {
                        *(exponent + 2 - i) = *(encoding + 3 - i);
                }
                decoded_mantissa = decode_fixed_point(mantissa, 4);
                decoded_exponent = decode_exzess_q(exponent, pow(2, bits - mantissa_pre_sign - 1) - 1);
                decoded_mantissa = decoded_mantissa + 1;
                decode = decoded_mantissa * pow(2, decoded_exponent);

                printf("\nDas Vorzeichenbit: %c\n", *encoding);
                printf("\nDer Exponent: %f\n", decoded_exponent);
                printf("\nDie Mantisse: %f\n", decoded_mantissa);

                if (*(encoding) == '1')
                {
                        decode = decode * -1;
                }

                free(mantissa);
                free(exponent);
                return decode;
        }
        else if (bits == 16 && mantissa_pre_sign == 11)
        {
                mantissa = malloc(10 * sizeof(char));
                exponent = malloc(5 * sizeof(char));
                if (mantissa == NULL || exponent == NULL)
                {
                        ALLOCATION_ERROR_MESSAGE();
                        return ALLOCATION_ERROR;
                }
                for (i = 0; i < 10; ++i)
                {
                        *(mantissa + 9 - i) = *(encoding + 15 - i);
                }
                printf("\nDie codierte  Mantisse: ");
                for (i = 0; i < 10; ++i)
                {
                        printf("%c", *(mantissa + i));
                }
                printf("\n");
                for (i = 0; i < 5; ++i)
                {
                        *(exponent + 4 - i) = *(encoding + 5 - i);
                }
                decoded_mantissa = decode_fixed_point(mantissa, 10);
                decoded_exponent = decode_exzess_q(exponent, pow(2, bits - mantissa_pre_sign - 1) - 1);
                decoded_mantissa = decoded_mantissa + 1;
                decode = decoded_mantissa * pow(2, decoded_exponent);

                printf("\nDas Vorzeichenbit: %c\n", *encoding);
                printf("\nDer Exponent: %f\n", decoded_exponent);
                printf("\nDie Mantisse: %f\n", decoded_mantissa);

                if (*(encoding) == '1')
                {
                        decode = decode * -1;
                }

                free(mantissa);
                free(exponent);
                return decode;
        }
        else if (bits == 32 && mantissa_pre_sign == 24)
        {
                mantissa = malloc(23 * sizeof(char));
                exponent = malloc(8 * sizeof(char));
                if (mantissa == NULL || exponent == NULL)
                {
                        ALLOCATION_ERROR_MESSAGE();
                        return ALLOCATION_ERROR;
                }
                for (i = 0; i < 23; ++i)
                {
                        *(mantissa + 22 - i) = *(encoding + 31 - i);
                }
                printf("\nDie codierte  Mantisse: ");
                for (i = 0; i < 23; ++i)
                {
                        printf("%c", *(mantissa + i));
                }
                printf("\n");
                for (i = 0; i < 8; ++i)
                {
                        *(exponent + 7 - i) = *(encoding + 8 - i);
                }
                decoded_mantissa = decode_fixed_point(mantissa, 23);
                decoded_exponent = decode_exzess_q(exponent, pow(2, bits - mantissa_pre_sign - 1) - 1);
                decoded_mantissa = decoded_mantissa + 1;
                decode = decoded_mantissa * pow(2, decoded_exponent);

                printf("\nDas Vorzeichenbit: %c\n", *encoding);
                printf("\nDer Exponent: %f\n", decoded_exponent);
                printf("\nDie Mantisse: %f\n", decoded_mantissa);

                if (*(encoding) == '1')
                {
                        decode = decode * -1;
                }

                free(mantissa);
                free(exponent);
                return decode;
        }
        else
        {
                FALSE_VALUE_MESSAGE();
                return FALSE_VALUE;
        }
}