#ifndef FOUR_BIT_INC_H
#define FOUR_BIT_INC_H

#include "../core/bit_sets.h"

struct four_bit_inc {
  nibble in;
  nibble out;
  wire_t* carry;
};

typedef struct four_bit_inc four_bit_inc;

void fbi_update(four_bit_inc*);

#endif