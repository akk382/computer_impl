/*
Notice the XOR result is exactly opposite of what equality requires:

A	B	XOR	Equal
0	0	0	1
0	1	1	0
1	0	1	0
1	1	0	1

Therefore:

Equal(A, B) = NOT(XOR(A, B))

Then the complete numbers are equal only when:

e0 AND e1 AND e2 AND e3

Since our AND gate accepts only two inputs, three AND gates combine four equality signals.
*/

#include "comparator.h"
#include "four_bit_not.h"
#include "four_bit_xor.h"
#include "and.h"

void fbc_update(four_bit_comparator* fbc) {
  four_bit_xor fbx;
  four_bit_not fbn;
  and_t and0, and1, and2;

  wire_t fbx_b0, fbx_b1, fbx_b2, fbx_b3;
  wire_t fbn_b0, fbn_b1, fbn_b2, fbn_b3;
  nibble fbx_out = {&fbx_b0, &fbx_b1, &fbx_b2, &fbx_b3};
  nibble fbn_out = {&fbn_b0, &fbn_b1, &fbn_b2, &fbn_b3};

  wire_t and0_out, and1_out;

  fbx.in1 = fbc->in1;
  fbx.in2 = fbc->in2;
  fbx.out = fbx_out;

  fbn.in = fbx.out;
  fbn.out = fbn_out;

  and0.in1 = fbn.out.bit0;
  and0.in2 = fbn.out.bit1;
  and0.out = &and0_out;

  and1.in1 = and0.out;
  and1.in2 = fbn.out.bit2;
  and1.out = &and1_out;

  and2.in1 = and1.out;
  and2.in2 = fbn.out.bit3;
  and2.out = fbc->result;

  fbx_update(&fbx);
  fbn_update(&fbn);
  and_update(&and0);
  and_update(&and1);
  and_update(&and2);
}