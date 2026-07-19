#ifndef FOUR_BIT_ADDER_H
#define FOUR_BIT_ADDER_H

#include "../core/bit_sets.h"

struct four_bit_adder {
  nibble in1;
  nibble in2;
  nibble sum;
  wire_t* carry; // overflow bit;
};

typedef struct four_bit_adder four_bit_adder;

void fba_update(four_bit_adder*);

#endif