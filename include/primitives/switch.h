#ifndef SWITCH_H
#define SWITCH_H

#include "../core/wire.h"

struct e_switch {
  wire_t* input;
  wire_t* control;
  wire_t* output;
};

typedef struct e_switch switch_t;

void switch_update(const switch_t*);

#endif