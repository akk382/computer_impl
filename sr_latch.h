#ifndef SR_LATCH_H
#define SR_LATCH_H

#include "wire.h"

struct sr_latch {
  // S = HIGH and R = HIGH is forbidden state and should not be initialized to those.
  // S = HIGH, R = LOW is a Set state. Sets Q to HIGH
  // S = LOW, R = HIGH is a Reset state. Sets Q to LOW
  // S = LOW, R = LOW is a Hold state. maintains previous values in Q, Qb.
  wire_t* S;
  wire_t* R;

  // The caller should initialize these to proper values, HIGH/LOW. 
  // Beause C initializes them to garbage values.
  wire_t* Q;
  wire_t* Qb; // Qb = Q bar = NOT(Q)
};

typedef struct sr_latch sr_latch;

void srl_update(sr_latch*);

#endif