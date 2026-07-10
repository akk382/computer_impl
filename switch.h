#ifndef SWITCH_H
#define SWITCH_H

#include "wire.h"

struct e_switch {
  wire_t* input;
  wire_t* control;
  wire_t* output;
};

typedef struct e_switch switch_t;

inline void switch_update(switch_t*);

#endif