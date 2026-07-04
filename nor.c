/*
Takes two inputs(control wires/gates)
NOR = NOT(OR)

0, 0 -> 1
0, 1 -> 0
1, 0 -> 0
1, 1 -> 0

CMOS: (Inverter) = NOT gate
0 -> 1
1 -> 0

We have to use pmos and nmos to reason about it.
From the NOR truth table:
if any of the input is high, it's getting pulled down. -> two nmos should be in parallel.
If both are low, it's getting pulled up -> two pmos should be in series.
*/

#include "nor.h"
#include "pmos_net.h"
#include "nmos_net.h"
#include "wire.h"

void nor_update(nor_t* nor) {
  pmos_net pn; // series network
  nmos_net nn; // parallel network

  pmos_t p1, p2;
  nmos_t n1, n2;

  wire_t p1_drn, p1_src, p2_drn;
  wire_t n_src, n1_drn, n2_drn;

  wire_t p_drn, n_drn;

  pn.p1 = &p1;
  pn.p2 = &p2;
  pn.drain = &p_drn;

  nn.n1 = &n1;
  nn.n2 = &n2;
  nn.drain = &n_drn;

  p1_src.val = HIGH;
  pn.p1->source = &p1_src;
  pn.p1->gate = nor->in1;
  pn.p1->drain = &p1_drn;
  pn.p2->gate = nor->in2;
  pn.p2->drain = &p2_drn;

  n_src.val = LOW;
  nn.n1->source = nn.n2->source = &n_src;
  nn.n1->gate = nor->in1;
  nn.n1->drain = &n1_drn;
  nn.n2->gate = nor->in2;
  nn.n2->drain = &n2_drn;

  pmos_series_update(&pn);
  nmos_parallel_update(&nn);

  if (pn.drain->val == HIGH) {
    if (nn.drain->val == LOW) {
      nor->out->val = CONFLICT;
    } else {
      nor->out->val = HIGH;
    }
  } else {
    if (nn.drain->val == LOW) {
      nor->out->val = LOW;
    } else {
      nor->out->val = FLOATING;
    }
  }  
}