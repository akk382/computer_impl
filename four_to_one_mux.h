#ifndef FOUR_TO_ONE_MUX_H
#define FOUR_TO_ONE_MUX_H

#include "wire.h"

struct four_to_one_mux {
  wire_t* in0;
  wire_t* in1;
  wire_t* in2;
  wire_t* in3;

  wire_t* sel0;
  wire_t* sel1;

  wire_t* out;
};

typedef struct four_to_one_mux four_to_one_mux;

void fto_mux_update(four_to_one_mux*);


#endif