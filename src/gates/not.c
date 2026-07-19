/*
NOT Truth Table:
0 -> 1
1 -> 0

NAND Truth Table:
0 0 -> 1
0 1 -> 1 dont care
1 0 -> 1 dont care
1 1 -> 0

From the above, we can see that when both the inputs are same it is flipping the input
We can just connect same input to two inputs of NAND gate and it will become a NOT gate.
*/

#include "../../include/gates/not.h"
#include "../../include/gates/nand.h"

void not_update(not_t* nt) {
  nand_t nd;
  wire_t result;
  nd.in1 = nt->in;
  nd.in2 = nt->in;
  nd.out = &result;

  nand_update(&nd);

  nt->out->val = result.val;
}