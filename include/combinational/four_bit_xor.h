#ifndef FOUR_BIT_XOR_H
#define FOUR_BIT_XOR_H

#include "../core/bit_sets.h"

// 4-bit (4 bits in each input) Just a 4 XOR gates, nothing special.

struct four_bit_xor {
  nibble in1;
  nibble in2;
  nibble out;
};

typedef struct four_bit_xor four_bit_xor;

void fbx_update(four_bit_xor*);

#endif