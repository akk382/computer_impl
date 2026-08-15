#ifndef FOUR_BIT_AND_H
#define FOUR_BIT_AND_H

#include "../core/bit_sets.h"

// 4-bit(4 bits in each input) Just a 4 and gates, nothing special.

struct four_bit_and {
  nibble in1;
  nibble in2;
  nibble out;
};

typedef struct four_bit_and four_bit_and;

void four_bit_and_update(const four_bit_and*);

#endif