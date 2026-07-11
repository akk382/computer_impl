#ifndef DEMUX_H
#define DEMUX_H

#include "wire.h"

struct demux {
  wire_t* in;
  wire_t* sel;
  wire_t* out0;
  wire_t* out1;
};

typedef struct demux demux_t;

void demux_update(demux_t*);

#endif