#ifndef FOUR_BIT_AND_H
#define FOUR_BIT_AND_H

#include "bit_sets.h"

// 4-bit(4 bits in each input) Just a 4 and gates, nothing special.

struct four_bit_and {
  nibble in1;
  nibble in2;
  nibble out;
};

typedef struct four_bit_and four_bit_and;

// TODO: not defined
void fband_update(four_bit_and*);

#endif