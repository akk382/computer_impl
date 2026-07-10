#include "demux.h"
#include "and.h"
#include "not.h"
#include "wire.h"

void demux_update(demux_t* dmx) {
  and_t and0, and1;
  not_t nt;
  wire_t nt_out;

  nt.in = dmx->sel;
  nt.out = &nt_out;

  and0.in1 = dmx->in;
  and0.in2 = nt.out;
  and0.out = dmx->out0;

  and1.in1 = dmx->in;
  and1.in2 = dmx->sel;
  and1.out = dmx->out1;

  not_update(&nt);
  and_update(&and0);
  and_update(&and1);
}