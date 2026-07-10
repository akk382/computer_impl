#ifndef TWO_BIT_ADDER_H
#define TWO_BIT_ADDER_H

#include "bit_sets.h"

struct two_bit_adder {
  two_bit in1;
  two_bit in2;
  two_bit sum;
  wire_t* carry;
};

typedef struct two_bit_adder two_bit_adder;

void tba_update(two_bit_adder*);

#endif