#ifndef FOUR_BIT_REG_H
#define FOUR_BIT_REG_H

#include "../core/bit_sets.h"
#include "../core/wire.h"

struct four_bit_reg {
  wire_t* LOAD;
  wire_t* CLK;

  nibble D;

  nibble Qm;
  nibble Qmb;
  nibble Q;
  nibble Qb;
};

typedef struct four_bit_reg four_bit_reg;

void fbr_update(four_bit_reg*);

#endif //FOUR_BIT_REG_H
