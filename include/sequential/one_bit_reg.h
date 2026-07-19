#ifndef ONE_BIT_REG_H
#define ONE_BIT_REG_H

#include "../core/wire.h"

struct one_bit_reg {
  wire_t* LOAD;
  wire_t* CLK;
  wire_t* D; // for external data. We won't connect it directly to D-FlipFlop. We multiplex it with Q on LOAD.

  wire_t* Qm;
  wire_t* Qmb;
  wire_t* Q;
  wire_t* Qb;
};

typedef struct one_bit_reg one_bit_reg;

void obreg_update(const one_bit_reg*);

#endif //ONE_BIT_REG_H
