#ifndef FOUR_BIT_TIMER_H
#define FOUR_BIT_TIMER_H

#include "../core/wire.h"
#include "../core/bit_sets.h"
#include "../../include/timing/four_bit_counter.h"

struct four_bit_timer
{
  wire_t* CLK;
  wire_t* EN;
  wire_t* RST;

  // current value storing register persistent values
  nibble OUT; // counter out

  // limit register inputs
  nibble LIMIT_D;
  wire_t* LIMIT_LOAD;

  // persistent wires of limit register to sustain state across updates.
  // Should be initialized while creating the timer object.
  nibble LIMIT_Q;
  nibble LIMIT_Qb;
  nibble LIMIT_Qm;
  nibble LIMIT_Qmb;

  // persistent sub-component, to sustain state across updates(We could also have used the persistent wires of these sub-component instead.)
  four_bit_counter_t counter;

  wire_t* IRQ; // interrupt line (high when the comparator result is HIGH)
};

typedef struct four_bit_timer four_bit_timer_t;

void four_bit_timer_update(four_bit_timer_t*);

#endif //FOUR_BIT_TIMER_H
