#ifndef FULL_ADDER_H
#define FULL_ADDER_H

#include "wire.h"

struct full_adder {
  wire_t* in1;
  wire_t* in2;
  wire_t* c_in; // carry_in
  wire_t* sum; // 
  wire_t* c_out; // carry_out
};

typedef struct full_adder full_adder;

void fa_update(full_adder*);

#endif