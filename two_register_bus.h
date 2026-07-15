#ifndef TWO_REGISTER_BUS_H
#define TWO_REGISTER_BUS_H

#include "bit_sets.h"

/**
 * R0.Q ── OE buffer ── r0_driver ┐
 *                                ├── resolver ── BUS
 * R1.Q ── OE buffer ── r1_driver ┘
 */
struct two_register_bus {
  nibble r0_Q;
  wire_t* r0_OE;

  nibble r1_Q;
  wire_t* r1_OE;

  nibble bus;
};

typedef struct two_register_bus two_register_bus_t;

void trb_update(const two_register_bus_t*);

#endif //TWO_REGISTER_BUS_H
