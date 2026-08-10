#ifndef FOUR_BIT_COUNTER_H
#define FOUR_BIT_COUNTER_H

#include "../core/wire.h"
#include "../core/bit_sets.h"

struct four_bit_counter
{
  wire_t* CLK;
  wire_t* EN;
  wire_t* RST;

  nibble out; // Q of the register that holds the current value

  /*
   * Private persistent wires for the internal 4-bit register.
   * Other components should not use these directly.
   */
  wire_t qb0;
  wire_t qb1;
  wire_t qb2;
  wire_t qb3;

  wire_t qm0;
  wire_t qm1;
  wire_t qm2;
  wire_t qm3;

  wire_t qmb0;
  wire_t qmb1;
  wire_t qmb2;
  wire_t qmb3;
};

typedef struct four_bit_counter four_bit_counter_t;

void four_bit_counter_update(four_bit_counter_t*);

#endif //FOUR_BIT_COUNTER_H
