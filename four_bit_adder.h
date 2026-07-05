#include "bit_sets.h"

struct four_bit_adder {
  nibble in1;
  nibble in2;
  nibble sum;
  wire_t* carry; 
};

typedef struct four_bit_adder four_bit_adder;

void fba_update(four_bit_adder*);