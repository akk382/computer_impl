#include "one_bit_oe_buffer.h"
#include "switch.h"

void oboe_update(const one_bit_oe_buffer_t* obb) {
  switch_t sw;

  sw.input = obb->Q;
  sw.control = obb->OE;
  sw.output = obb->bus;

  switch_update(&sw);
}
