#include "../../include/bus/two_register_bus.h"

#include "../../include/bus/four_bit_bus_conflict_resolver.h"
#include "../../include/bus/four_bit_oe_buffer.h"

void trb_update(const two_register_bus_t* trb) {
  four_bit_oe_buffer_t fboeb0, fboeb1;
  four_bit_bus_conflict_resolver_t fbbcr;

  wire_t wire0 = { FLOATING };
  wire_t wire1 = { FLOATING };
  wire_t wire2 = { FLOATING };
  wire_t wire3 = { FLOATING };

  wire_t wire4 = { FLOATING };
  wire_t wire5 = { FLOATING };
  wire_t wire6 = { FLOATING };
  wire_t wire7 = { FLOATING };

  nibble buffer_bus0 = { &wire0, &wire1, &wire2, &wire3 };
  nibble buffer_bus1 = { &wire4, &wire5, &wire6, &wire7 };

  fboeb0.Q = trb->r0_Q;
  fboeb0.OE = trb->r0_OE;
  fboeb0.bus = buffer_bus0;

  fboeb1.Q = trb->r1_Q;
  fboeb1.OE = trb->r1_OE;
  fboeb1.bus = buffer_bus1;

  fboeb_update(&fboeb0);
  fboeb_update(&fboeb1);

  fbbcr.driver0 = buffer_bus0;
  fbbcr.driver1 = buffer_bus1;
  fbbcr.bus = trb->bus;

  fbbcr_update(&fbbcr);
}