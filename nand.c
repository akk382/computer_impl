
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

