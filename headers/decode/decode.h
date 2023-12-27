#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED


/*Decodes the exzess-q encoding which is written in the char pointer concerning the given q-value. Returns the decoded value.*/
double decode_exzess_q(char *encoding, int q);
/*Decodes the fixed point encoding which is written in the char pointer concerning the given amount of after coma digits which were used in the encoding. Returns the decoded value.*/
double decode_fixed_point(char *encoding, int after_coma);

#endif