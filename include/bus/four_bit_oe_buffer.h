#ifndef FOUR_BIT_OE_BUFFER_H
#define FOUR_BIT_OE_BUFFER_H

#include "../core/bit_sets.h"
#include "../core/wire.h"

struct four_bit_oe_buffer {
  nibble Q;
  wire_t* OE;
  nibble bus; // This is the private bus to this component. Not the actual bus.
};

typedef struct four_bit_oe_buffer four_bit_oe_buffer_t;

void fboeb_update(const four_bit_oe_buffer_t*);

#endif //FOUR_BIT_OE_BUFFER_H
