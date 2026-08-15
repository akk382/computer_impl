#ifndef FOUR_BIT_OR_H
#define FOUR_BIT_OR_H

#include "../core/bit_sets.h"

struct four_bit_or
{
  nibble in0;
  nibble in1;

  nibble out;
};

typedef struct four_bit_or four_bit_or_t;

void four_bit_or_update(const four_bit_or_t*);

#endif //FOUR_BIT_OR_H
