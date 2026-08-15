#ifndef THREE_DRIVER_BUS_RESOLVER_H
#define THREE_DRIVER_BUS_RESOLVER_H

#include "../core/bit_sets.h"

struct three_driver_bus_resolver
{
  nibble driver0;
  nibble driver1;
  nibble driver2;

  nibble bus;
};

typedef struct three_driver_bus_resolver three_driver_bus_resolver_t;

void three_driver_bus_resolver_update(const three_driver_bus_resolver_t*);

#endif //THREE_DRIVER_BUS_RESOLVER_H
