#ifndef THREE_SOURCE_BUS_H
#define THREE_SOURCE_BUS_H

#include "../core/bit_sets.h"

struct three_source_bus
{
  nibble source0;
  wire_t* source0_OE;

  nibble source1;
  wire_t* source1_OE;

  nibble source2;
  wire_t* source2_OE;

  nibble bus;
};

typedef struct three_source_bus three_source_bus_t;

void three_source_bus_update(const three_source_bus_t*);

#endif //THREE_SOURCE_BUS_H
