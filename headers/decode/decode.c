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
        int digits = (int)strlen(encoding);
        int power = 0;
        double decode = 0;

        while (digits != 0)
        {
                decode = decode + (int)(*(encoding + digits - 1) - 48) * pow(2, power);
                ++power;
                --digits;
        }

        decode = decode / pow(2, after_coma);
        return decode;
}