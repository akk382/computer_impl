#ifndef FOUR_BIT_OE_BUFFER_H
#define FOUR_BIT_OE_BUFFER_H

#include "bit_sets.h"
#include "wire.h"

struct four_bit_oe_buffer {
  nibble Q;
  wire_t* OE;
  nibble bus;
};

typedef struct four_bit_oe_buffer four_bit_oe_buffer_t;

void fboeb_update(const four_bit_oe_buffer_t*);

#endif //FOUR_BIT_OE_BUFFER_H
