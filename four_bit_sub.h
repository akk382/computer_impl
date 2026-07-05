#include "bit_sets.h"

struct four_bit_sub {
  nibble in1;
  nibble in2;
  nibble out;
};

typedef struct four_bit_sub four_bit_sub;

void fbs_update(four_bit_sub*);