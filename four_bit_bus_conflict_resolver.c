#include "four_bit_bus_conflict_resolver.h"
#include "bus_conflict_resolver.h"


void fbbcr_update(const four_bit_bus_conflict_resolver_t* fbbcr) {
  bus_conflict_resolver_t bcr0, bcr1, bcr2, bcr3;

  bcr0.driver0 = fbbcr->driver0.bit0;
  bcr0.driver1 = fbbcr->driver1.bit0;
  bcr0.bus = fbbcr->bus.bit0;

  bcr1.driver0 = fbbcr->driver0.bit1;
  bcr1.driver1 = fbbcr->driver1.bit1;
  bcr1.bus = fbbcr->bus.bit1;

  bcr2.driver0 = fbbcr->driver0.bit2;
  bcr2.driver1 = fbbcr->driver1.bit2;
  bcr2.bus = fbbcr->bus.bit2;

  bcr3.driver0 = fbbcr->driver0.bit3;
  bcr3.driver1 = fbbcr->driver1.bit3;
  bcr3.bus = fbbcr->bus.bit3;

  bcr_update(&bcr0);
  bcr_update(&bcr1);
  bcr_update(&bcr2);
  bcr_update(&bcr3);
}