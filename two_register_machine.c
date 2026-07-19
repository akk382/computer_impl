#include "two_register_machine.h"
#include "two_register_bus.h"
#include "four_bit_reg.h"

void trm_update(two_register_machine_t* trm) {
  two_register_bus_t trb;
  trb.r0_Q = trm->R0->Q;
  trb.r1_Q = trm->R1->Q;
  trb.r0_OE = trm->r0_OE;
  trb.r1_OE = trm->r1_OE;
  trb.bus = trm->bus;

  trb_update(&trb);

  trm->R0->D = trm->bus;
  trm->R1->D = trm->bus;
  fbr_update(trm->R0);
  fbr_update(trm->R1);
}