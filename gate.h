#ifndef GATE_H
#define GATE_H

#include "wire.h"

struct unary_gate {
  wire_t* in;
  wire_t* out;
};

struct bin_gate {
  wire_t* in1;
  wire_t* in2;
  wire_t* out;
};

typedef struct bin_gate bin_gate_t;
typedef struct unary_gate uni_gate;

#endif