/*
AND Truth Table:
0 0 -> 0
0 1 -> 0
1 0 -> 0
1 1 -> 1

NAND Truth Table:
0 0 -> 1
0 1 -> 1
1 0 -> 1
1 1 -> 0

NOT Truth Table:
0 -> 1
1 -> 0

From the above three Truth Tables we can observe, AND is just a flipped version of NAND.
So we can apply NOT to the result of NAND.
*/

#include "../../include/gates/and.h"
#include "../../include/gates/nand.h"
#include "../../include/gates/not.h"

void and_update(and_t* a) {
  nand_t nd;
  not_t nt;
  wire_t nd_out;

  nd.in1 = a->in1;
  nd.in2 = a->in2;
  nd.out = &nd_out;

  nt.in = nd.out;
  nt.out = a->out;

  nand_update(&nd);
  not_update(&nt);
}