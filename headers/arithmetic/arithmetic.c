#include "arithmetic.h"
#include "encode.h"
#include "decode.h"
#include "bits.h"
#include <stdio.h>
#include <stdlib.h>

double add_floating_point(double x, double y, int mantissa_pre_sign)
{
        double result, x_mantissa, y_mantissa;
        char *x_binary = initialize_bitfield();
        char *y_binary = initialize_bitfield();
        char *added_binaries;
        int x_exponent, y_exponent, i, result_exponent;

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
                *(added_binaries + 31 + mantissa_pre_sign - 1) == '1';
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