#include "../../include/bus/three_source_bus.h"
#include "../../include/bus/four_bit_oe_buffer.h"
#include "../../include/bus/three_driver_bus_resolver.h"


void three_source_bus_update(const three_source_bus_t* tsb)
{
  three_driver_bus_resolver_t tdbr;
  four_bit_oe_buffer_t fboe0, fboe1, fboe2;

  wire_t d00 = {FLOATING}, d01 = {FLOATING}, d02 = {FLOATING}, d03 = {FLOATING};
  wire_t d10 = {FLOATING}, d11 = {FLOATING}, d12 = {FLOATING}, d13 = {FLOATING};
  wire_t d20 = {FLOATING}, d21 = {FLOATING}, d22 = {FLOATING}, d23 = {FLOATING};
  nibble temp_driver0 = { &d00, &d01, &d02, &d03 };
  nibble temp_driver1 = { &d10, &d11, &d12, &d13 };
  nibble temp_driver2 = { &d20, &d21, &d22, &d23 };

  fboe0.Q = tsb->source0;
  fboe0.OE = tsb->source0_OE;
  fboe0.bus = temp_driver0;

  fboe1.Q = tsb->source1;
  fboe1.OE = tsb->source1_OE;
  fboe1.bus = temp_driver1;

  fboe2.Q = tsb->source2;
  fboe2.OE = tsb->source2_OE;
  fboe2.bus = temp_driver2;

  tdbr.driver0 = temp_driver0;
  tdbr.driver1 = temp_driver1;
  tdbr.driver2 = temp_driver2;
  tdbr.bus = tsb->bus;

  fboeb_update(&fboe0);
  fboeb_update(&fboe1);
  fboeb_update(&fboe2);
  three_driver_bus_resolver_update(&tdbr);
}
