
/*
Takes two inputs(control wires/gates)
NAND = NOT(AND)

0, 0 -> 1
0, 1 -> 1
1, 0 -> 1
1, 1 -> 0

CMOS: (Inverter) = NOT gate
0 -> 1
1 -> 0

We have to use pmos and nmos to reason about it.
From the NAND truth table:
if any of the input is low, it's getting pulled up. -> two pmos should be in parallel.
If both are high, it's getting pulled down -> two nmos should be in series.

*/

#include "nand.h"
#include "wire.h"
#include "pmos_net.h"
#include "nmos_net.h"

void nand_update(nand_t* nd) {
  pmos_net pn; // parallel network
  nmos_net nn; // series network

  pmos_t p1, p2;
  nmos_t n1, n2;

  pn.p1 = &p1;
  pn.p2 = &p2;

  nn.n1 = &n1;
  nn.n2 = &n2;

  wire_t p_src, p1_drn;
  wire_t p2_drn;
  wire_t p_drn;
  wire_t n1_drn;
  wire_t n2_src, n2_drn;
  wire_t n_drn;

  p_src.val = HIGH;
  pn.p1->source = &p_src;
  pn.p1->gate = nd->in1;
  pn.p1->drain = &p1_drn;

  pn.p2->gate = nd->in2;
  pn.p2->source = &p_src;
  pn.p2->drain = &p2_drn;

  pn.drain = &p_drn;

  
  nn.n1->gate = nd->in1;
  nn.n1->drain = &n1_drn;

  n2_src.val = LOW;
  nn.n2->source = &n2_src;
  nn.n2->gate = nd->in2;
  nn.n2->drain = &n2_drn;

  nn.drain = &n_drn;

  pmos_parallel_update(&pn);
  nmos_series_update(&nn);

  if (pn.drain->val == HIGH) {
    if (nn.drain->val == LOW) {
      nd->out->val = CONFLICT;
    } else {
      nd->out->val = HIGH;
    }
  } else {
    if (nn.drain->val == LOW) {
      nd->out->val = LOW;
    } else {
      nd->out->val = FLOATING;
    }
  }
}
