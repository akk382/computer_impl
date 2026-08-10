/**
*A clock is just a wire that changes like this:

LOW -> HIGH -> LOW -> HIGH -> LOW ...

The important moment for our registers is:

LOW -> HIGH

That is the rising edge.
 */


#ifndef CLOCK_H
#define CLOCK_H

#include "../core/wire.h"

struct clock
{
  wire_t* out;
};

typedef struct clock clock_t;

void clock_low(const clock_t*);
void clock_high(const clock_t*);
void clock_tick(const clock_t*);

#endif //CLOCK_H
