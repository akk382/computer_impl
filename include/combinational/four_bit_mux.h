#ifndef FOUR_BIT_MULTIPLEXER_H
#define FOUR_BIT_MULTIPLEXER_H

#include "../core/bit_sets.h"
#include "../core/wire.h"

struct four_bit_mux {
  nibble in0;
  nibble in1;
  
  wire_t* sel;

  nibble out;
};

typedef struct four_bit_mux four_bit_mux;

void fmb_update(four_bit_mux*);

#endif