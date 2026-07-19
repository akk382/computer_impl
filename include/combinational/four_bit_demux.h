#ifndef FOUR_BIT_DEMUX_H
#define FOUR_BIT_DEMUX_H

#include "../core/bit_sets.h"
#include "../core/wire.h"

struct four_bit_demux {
  nibble in;
  wire_t* sel;
  nibble out0;
  nibble out1;
};

typedef struct four_bit_demux four_bit_demux;

void fbd_update(four_bit_demux*);

#endif