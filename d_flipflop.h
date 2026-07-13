/*
 * A D flip-flop, which changes Q only at a clock transition instead of during the entire HIGH level.
 */


#ifndef D_FLIPFLOP_H
#define D_FLIPFLOP_H
#include "wire.h"

// CLK, D, Qm, Qmb should contain valid values
struct d_flipflop {
  wire_t* CLK;

  wire_t* D;

  wire_t* Qm; // Master D-latch Q
  wire_t* Qmb; // Master D-latch Qb

  wire_t* Q; // Slave D-latch Q
  wire_t* Qb; // Slave D-latch Qb
};

typedef struct d_flipflop d_flipflop;

void dff_update(const d_flipflop*);

#endif //D_FLIPFLOP_H
