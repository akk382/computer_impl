#ifndef FOUR_BIT_BUS_CONFLICT_RESOLVER_H
#define FOUR_BIT_BUS_CONFLICT_RESOLVER_H

#include "../core/bit_sets.h"

struct four_bit_bus_conflict_resolver {
  nibble driver0;
  nibble driver1;

  nibble bus;
};

typedef struct four_bit_bus_conflict_resolver four_bit_bus_conflict_resolver_t;

void fbbcr_update(const four_bit_bus_conflict_resolver_t*);

#endif //FOUR_BIT_BUS_CONFLICT_RESOLVER_H
