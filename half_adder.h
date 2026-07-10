#ifndef HALF_ADDER_H
#define HALF_ADDER_H

#include "wire.h"

struct half_adder {
  wire_t* in1;
  wire_t* in2;
  wire_t* sum;  // XOR(in1, in2)
  wire_t* carry; // AND(in1, in2)
};

typedef struct half_adder half_adder;

void ha_update(half_adder*);

#endif