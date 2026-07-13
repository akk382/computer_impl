/*
 * A D latch is level-sensitive.
 * Changes Q during the entire HIGH level of D
 * E = HIGH  → Q follows D
 * E = LOW   → Q remembers its previous value
 */
#ifndef D_LATCH_H
#define D_LATCH_H
#include "wire.h"

struct d_latch {
  wire_t* E; // Enable
  wire_t* D;

  wire_t* Q;
  wire_t* Qb;
};

typedef struct d_latch d_latch;

void dl_update(const d_latch*);

#endif
