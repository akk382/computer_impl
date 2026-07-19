/*
OR Truth Table:
0 0 -> 0
0 1 -> 1
1 0 -> 1
1 1 -> 1

NAND Truth Table:
0 0 -> 1 -> we want it to be 0
0 1 -> 1 -> this one gives the same output even if we flip, because of the below row.
1 0 -> 1
1 1 -> 0 -> we want it to be 1

Can we somehow flip both the inputs and send it to the NAND gate?

NOT Truth Table:
0 -> 1
1 -> 0

We can add a NOT gate to each input and send the result of that to the input of NAND and we get OR
*/

#include "../../include/gates/or.h"
#include "../../include/gates/not.h"
#include "../../include/gates/nand.h"

void or_update(or_t* o) {
  not_t nt1;
  not_t nt2;
  nand_t nd;

  wire_t nt1_out, nt2_out;

  nt1.in = o->in1;
  nt2.in = o->in2;
  nt1.out = &nt1_out;
  nt2.out = &nt2_out;

  nd.in1 = nt1.out;
  nd.in2 = nt2.out;
  nd.out = o->out;

  not_update(&nt1);
  not_update(&nt2);
  nand_update(&nd);
}