#ifndef FOUR_BIT_ALU_H
#define FOUR_BIT_ALU_H

#include "../core/bit_sets.h"

struct four_bit_alu
{
  nibble in0;
  nibble in1;

  wire_t* sel0;
  wire_t* sel1;

  nibble out;

  wire_t* carry;
};

typedef struct four_bit_alu four_bit_alu_t;

void four_bit_alu_update(const four_bit_alu_t*);

#endif //FOUR_BIT_ALU_H
