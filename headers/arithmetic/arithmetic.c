#include "arithmetic.h"
#include "encode.h"
#include "bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double add_floating_point(double x, double y, int mantissa_pre_sign)
{
        double result;
        char *x_binary = initialize_bitfield();
        char *y_binary = initialize_bitfield();
        char *added_binaries;
        int x_exponent, y_exponent, i, result_exponent;

        if (mantissa_pre_sign != 5 && mantissa_pre_sign != 11 && mantissa_pre_sign != 24)
        {
                INVALID_CALL();
                return INVALID_CALL_ERROR;
        }

        x_exponent = standardize_floating_point(x, &x);
        y_exponent = standardize_floating_point(y, &y);

        if (x_exponent < y_exponent)
        {
                result_exponent = y_exponent;
                while (x_exponent != y_exponent)
                {
                        x = x / 2;
                        ++x_exponent;
                }
        }
        else if (y_exponent < x_exponent)
        {
                result_exponent = x_exponent;
                while (y_exponent != x_exponent)
                {
                        y = y / 2;
                        ++y_exponent;
                }
        }
        else
        {
                result_exponent = x_exponent;
        }

        decimal_into_binary(x, x_binary);
        decimal_into_binary(y, y_binary);

        added_binaries = add_bitfields(x_binary, y_binary);

        if (*(added_binaries + 31 + mantissa_pre_sign) == '1' && *(added_binaries + 31 + mantissa_pre_sign - 1) == '0') /*rounding*/
        {
                *(added_binaries + 31 + mantissa_pre_sign - 1) = '1';
        }

        result = 0;
        for (i = 30; i >= 0; --i)
        {
                result = result + ((int)*(added_binaries + i) - 48) * pow(2, 30 - i);
        }
        for (i = 32; i < 32 + mantissa_pre_sign - 1; ++i)
        {
                result = result + ((int)*(added_binaries + i) - 48) * pow(2, 31 - i);
        }

        result = result * pow(2, result_exponent);
        free(x_binary);
        free(y_binary);
        free(added_binaries);
        return result;
}
double sub_floating_point(double x, double y, int mantissa_pre_sign)
{
        double result, x_origin, y_origin;
        char *x_binary = initialize_bitfield();
        char *y_binary = initialize_bitfield();
        char *subbed_binaries;
        int x_exponent, y_exponent, i, result_exponent;

        if (mantissa_pre_sign != 5 && mantissa_pre_sign != 11 && mantissa_pre_sign != 24)
        {
                INVALID_CALL();
                return INVALID_CALL_ERROR;
        }

        x_origin = x;
        y_origin = y;

        x_exponent = standardize_floating_point(x, &x);
        y_exponent = standardize_floating_point(y, &y);

        if (x_exponent < y_exponent)
        {
                result_exponent = y_exponent;
                while (x_exponent != y_exponent)
                {
                        x = x / 2;
                        ++x_exponent;
                }
        }
        else if (y_exponent < x_exponent)
        {
                result_exponent = x_exponent;
                while (y_exponent != x_exponent)
                {
                        y = y / 2;
                        ++y_exponent;
                }
        }
        else
        {
                result_exponent = x_exponent;
        }

        decimal_into_binary(x, x_binary);
        decimal_into_binary(y, y_binary);

        if (x > y)
        {
                subbed_binaries = sub_bitfields(x_binary, y_binary);
        }
        else
        {
                subbed_binaries = sub_bitfields(y_binary, x_binary);
        }

        if (*(subbed_binaries + 31 + mantissa_pre_sign) == '1' && *(subbed_binaries + 31 + mantissa_pre_sign - 1) == '0') /*rounding*/
        {
                *(subbed_binaries + 31 + mantissa_pre_sign - 1) = '1';
        }

        result = 0;
        for (i = 30; i >= 0; --i)
        {
                result = result + ((int)*(subbed_binaries + i) - 48) * pow(2, 30 - i);
        }
        for (i = 32; i < 32 + mantissa_pre_sign - 1; ++i)
        {
                result = result + ((int)*(subbed_binaries + i) - 48) * pow(2, 31 - i);
        }

        result = result * pow(2, result_exponent);
        if (y_origin > x_origin)
        {
                result = result * -1;
        }
        free(x_binary);
        free(y_binary);
        free(subbed_binaries);
        return result;
}