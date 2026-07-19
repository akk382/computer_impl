/*
XOR Truth Table:
0 0 -> 0
0 1 -> 1
1 0 -> 1
1 1 -> 0

NAND Truth Table:
0 0 -> 1
0 1 -> 1
1 0 -> 1
1 1 -> 0

Googles solution: (Check for ChatGPT's reasoning at the end of this file.)
N1 = NAND(X, Y)
N2 = NAND(X, N1)
N3 = NAND(N1, Y)
N4 = NAND(N2, N3)
*/

#include "../../include/gates/xor.h"
#include "../../include/gates/nand.h"
#include "../../include/core/wire.h"

void xor_update(xor_t* xr) {
  nand_t nd1, nd2, nd3, nd4;
  wire_t n1_out, n2_out, n3_out;

  nd1.in1 = xr->in1;
  nd1.in2 = xr->in2;
  nd1.out = &n1_out;

  nd2.in1 = xr->in1;
  nd2.in2 = nd1.out;
  nd2.out = &n2_out;

  nd3.in1 = xr->in2;
  nd3.in2 = nd1.out;
  nd3.out = &n3_out;

  nd4.in1 = nd2.out;
  nd4.in2 = nd3.out;

  nd4.out = xr->out;

  nand_update(&nd1);
  nand_update(&nd2);
  nand_update(&nd3);
  nand_update(&nd4);
}

/*
N1 is:

N1 = NAND(X, Y)

So:

when both inputs are HIGH, N1 = LOW
otherwise, N1 = HIGH

That makes N1 a shared signal saying:

“The inputs are not both HIGH.”

Then:

N2 = NAND(X, N1)
N3 = NAND(Y, N1)

These two gates isolate the two cases where exactly one input is HIGH.

For example:

X = HIGH
Y = LOW

Then:

N1 = HIGH
N2 = NAND(HIGH, HIGH) = LOW
N3 = NAND(LOW, HIGH)  = HIGH

Finally:

N4 = NAND(N2, N3)
   = NAND(LOW, HIGH)
   = HIGH

For both inputs HIGH:

N1 = LOW
N2 = NAND(HIGH, LOW) = HIGH
N3 = NAND(HIGH, LOW) = HIGH
N4 = NAND(HIGH, HIGH) = LOW

So the final NAND produces HIGH only when one of N2 or N3 becomes LOW, which happens when exactly one original input is HIGH.
*/