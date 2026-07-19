#ifndef ONE_TO_FOUR_DEMUX_H
#define ONE_TO_FOUR_DEMUX_H

#include "../core/wire.h"

struct one_to_four_demux {
  wire_t* in;

  wire_t* sel0;
  wire_t* sel1;

  wire_t* out0;
  wire_t* out1;
  wire_t* out2;
  wire_t* out3;
};

typedef struct one_to_four_demux one_to_four_demux;

void ot4demux_update(one_to_four_demux*);

#endif