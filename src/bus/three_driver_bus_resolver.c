#include "../../include/bus/three_driver_bus_resolver.h"
#include "../../include/bus/four_bit_bus_conflict_resolver.h"

void three_driver_bus_resolver_update(const three_driver_bus_resolver_t* tdbcr)
{
  four_bit_bus_conflict_resolver_t fbbcr0, fbbcr1;

  wire_t temp0 = { FLOATING };
  wire_t temp1 = { FLOATING };
  wire_t temp2 = { FLOATING };
  wire_t temp3 = { FLOATING };
  nibble temp_bus = { &temp0, &temp1, &temp2, &temp3 };

  fbbcr0.driver0 = tdbcr->driver0;
  fbbcr0.driver1 = tdbcr->driver1;
  fbbcr0.bus = temp_bus;

  fbbcr1.driver0 = temp_bus;
  fbbcr1.driver1 = tdbcr->driver2;
  fbbcr1.bus = tdbcr->bus;

  fbbcr_update(&fbbcr0);
  fbbcr_update(&fbbcr1);
}
