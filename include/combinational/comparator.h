#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "../core/bit_sets.h"
#include "../core/wire.h"

struct four_bit_comparator {
  nibble in1;
  nibble in2;
  wire_t* result;
};

typedef struct four_bit_comparator four_bit_comparator;

void fbc_update(four_bit_comparator*);

#endif