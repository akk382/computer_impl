#include "../../include/timing/four_bit_timer.h"

#include "../../include/combinational/comparator.h"
#include "../../include/timing/four_bit_counter.h"
#include "../../include/sequential/four_bit_reg.h"

/** Note:
 * This timer now is a level timer, not a latched interrupt timer.
* Later we can build a latched IRQ timer:

once OUT == LIMIT_Q:
    IRQ stays HIGH until ACK clears it
 */

void four_bit_timer_update(four_bit_timer_t* timer)
{
  // we need a limit register and a comparator,
  // timer already has counter as subcomponent,
  // because that need to sustain state across updates
  four_bit_comparator comparator;
  four_bit_reg limit_reg;

  timer->counter.CLK = timer->CLK;
  timer->counter.EN = timer->EN;
  timer->counter.RST = timer->RST;
  timer->counter.out = timer->OUT;

  limit_reg.CLK = timer->CLK;
  limit_reg.LOAD = timer->LIMIT_LOAD;
  limit_reg.D = timer->LIMIT_D;
  limit_reg.Qm = timer->LIMIT_Qm;
  limit_reg.Qmb = timer->LIMIT_Qmb;
  limit_reg.Q = timer->LIMIT_Q;
  limit_reg.Qb = timer->LIMIT_Qb;

  comparator.in1 = timer->OUT;
  comparator.in2 = timer->LIMIT_Q;
  comparator.result = timer->IRQ;

  fbr_update(&limit_reg);
  four_bit_counter_update(&timer->counter);
  fbc_update(&comparator);
}
