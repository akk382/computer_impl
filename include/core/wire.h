#ifndef WIRE_H
#define WIRE_H

#include "signal.h"

struct wire {
  signal_t val;
};

typedef struct wire wire_t;

#endif