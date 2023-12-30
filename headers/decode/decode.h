#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED

#define ALLOCATION_ERROR -90

/*Decodes the exzess-q encoding which is written in the char pointer concerning the given q-value. Returns the decoded value.*/
double decode_exzess_q(char *encoding, int q);
/*Decodes the fixed point encoding which is written in the char pointer concerning the given amount of after coma digits which were used in the encoding. Returns the decoded value.*/
double decode_fixed_point(char *encoding, int after_coma);
/*Decodes the given floating point encoding. Amount of bits used for non charackteristics has to be set to ensure the correct decoding. Returns the decoded value. Otherwise FALSE_VALUE. Input parameters have to be identical with the used parameters for the encoding of the given encoded sequence.*/
double decode_floating_point(char *encoding, int mantissa_pre_sign, int bits);

#endif