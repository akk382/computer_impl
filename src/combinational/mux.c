/*
1-bit multiplexer.

A multiplexer chooses one of two input wires.

select = LOW  → output follows A
select = HIGH → output follows B

Electronic idea:

One path should open only when select is LOW.
The other path should open only when select is HIGH.
The two selected paths are combined into one output.

Implement it using exactly:

one NOT gate,
two AND gates,
one OR gate.

We can think about it using sum of the products way.

When SEL is LOW, A is selected, and when SEL is HIGH, B is selected.

OUT = A.NOT(SEL) + B.SEL
*/

#include "../../include/combinational/mux.h"
#include "../../include/gates/or.h"
#include "../../include/gates/not.h"
#include "../../include/gates/and.h"

void obm_update(mux_t* obm) {
  or_t or;
  and_t and0, and1;
  not_t nt;
  wire_t nt_out, and0_out, and1_out;

  nt.in = obm->sel;
  nt.out = &nt_out;
  and0.in1 = obm->in0;
  and0.in2 = nt.out;
  and0.out = &and0_out;

  and1.in1 = obm->in1;
  and1.in2 = obm->sel;
  and1.out = &and1_out;

  or.in1 = and0.out;
  or.in2 = and1.out;

  or.out = obm->out;

  not_update(&nt);
  and_update(&and0);
  and_update(&and1);
  or_update(&or);
}