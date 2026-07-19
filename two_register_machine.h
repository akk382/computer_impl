#ifndef TWO_REGISTER_MACHINE_H
#define TWO_REGISTER_MACHINE_H

#include "four_bit_reg.h"

struct two_register_machine {
  four_bit_reg* R0; // Can load from and to the bus
  wire_t* r0_OE;

  four_bit_reg* R1; // Can load from and to the bus
  wire_t* r1_OE;

  nibble bus;
};

typedef struct two_register_machine two_register_machine_t;

void trm_update(two_register_machine_t*);

#endif //TWO_REGISTER_MACHINE_H
