#ifndef ONE_BIT_OE_BUFFER_H
#define ONE_BIT_OE_BUFFER_H

#include "../core/wire.h"

struct one_bit_oe_buffer {
  wire_t* Q; // input to switch

  wire_t* OE; // control to switch

  wire_t* bus; // output to switch
};

typedef struct one_bit_oe_buffer one_bit_oe_buffer_t;

void oboe_update(const one_bit_oe_buffer_t*);

#endif //ONE_BIT_OE_BUFFER_H
