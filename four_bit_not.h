#ifndef FOUR_BIT_NOT_H
#define FOUR_BIT_NOT_H

#include "bit_sets.h"

struct four_bit_not {
  nibble in;
  nibble out;
};

typedef struct four_bit_not four_bit_not;

void fbn_update(four_bit_not*);

#endif