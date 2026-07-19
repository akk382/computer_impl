#include "../../include/combinational/one_to_four_demux.h"
#include "../../include/gates/and.h"
#include "../../include/combinational/two_to_four_decoder.h"
#include "../../include/core/wire.h"

void ot4demux_update(one_to_four_demux* ot4d) {
  two_to_four_decoder tt4d;
  and_t and0, and1, and2, and3;

  wire_t decoder_out0, decoder_out1, decoder_out2, decoder_out3;

  tt4d.in0 = ot4d->sel0;
  tt4d.in1 = ot4d->sel1;
  tt4d.out0 = &decoder_out0;
  tt4d.out1 = &decoder_out1;
  tt4d.out2 = &decoder_out2;
  tt4d.out3 = &decoder_out3;

  and0.in1 = tt4d.out0;
  and0.in2 = ot4d->in;
  and0.out = ot4d->out0;

  and1.in1 = tt4d.out1;
  and1.in2 = ot4d->in;
  and1.out = ot4d->out1;

  and2.in1 = tt4d.out2;
  and2.in2 = ot4d->in;
  and2.out = ot4d->out2;

  and3.in1 = tt4d.out3;
  and3.in2 = ot4d->in;
  and3.out = ot4d->out3;

  tt4_decoder_update(&tt4d);
  and_update(&and0);
  and_update(&and1);
  and_update(&and2);
  and_update(&and3);
}