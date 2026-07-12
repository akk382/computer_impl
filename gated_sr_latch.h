#ifndef GATED_SR_LATCH_H
#define GATED_SR_LATCH_H

#include "wire.h"

struct gated_sr_latch {
  // When E is HIGH, the gate uses SR latch.
  // When E is LOW, the gate ignores SR latch and remembers previous state.
  wire_t* E; // Enable

  wire_t* S;
  wire_t* R;

  wire_t* Q;
  wire_t* Qb;
};

typedef struct gated_sr_latch gated_sr_latch_t;

void gsrl_update(const gated_sr_latch_t*);

#endif