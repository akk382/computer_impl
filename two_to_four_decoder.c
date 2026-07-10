#include "two_to_four_decoder.h"
#include "and.h"
#include "not.h"

void tt4_decoder_update(two_to_four_decoder* tt4d) {

  not_t n0, n1;

  and_t and0, and1, and2, and3;

  wire_t n0_out, n1_out;

  n0.in = tt4d->in0;
  n0.out = &n0_out;

  n1.in = tt4d->in1;
  n1.out = &n1_out;

  and0.in1 = n0.out;
  and0.in2 = n1.out;
  and0.out = tt4d->out0;

  and1.in1 = tt4d->in0;
  and1.in2 = n1.out;
  and1.out = tt4d->out1;

  and2.in1 = n0.out;
  and2.in2 = tt4d->in1;
  and2.out = tt4d->out2;

  and3.in1 = tt4d->in0;
  and3.in2 = tt4d->in1;
  and3.out = tt4d->out3;

  not_update(&n0);
  not_update(&n1);
  
  and_update(&and0);
  and_update(&and1);
  and_update(&and2);
  and_update(&and3);
}