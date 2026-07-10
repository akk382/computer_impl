#ifndef ONE_BIT_MULTIPLEXER_H
#define ONE_BIT_MULTIPLEXER_H

#include "wire.h"

struct mux {
  wire_t* in0;
  wire_t* in1;
  wire_t* sel;
  wire_t* out;
};

typedef struct mux mux_t;

void obm_update(mux_t*);

#endif