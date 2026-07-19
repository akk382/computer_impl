#ifndef BUS_CONFLICT_RESOLVER_H
#define BUS_CONFLICT_RESOLVER_H

#include "../core/wire.h"

struct bus_conflict_resolver {
  wire_t* driver0;
  wire_t* driver1;

  wire_t* bus;
};

typedef  struct bus_conflict_resolver bus_conflict_resolver_t;

void bcr_update(const bus_conflict_resolver_t*);

#endif //BUS_CONFLICT_RESOLVER_H
