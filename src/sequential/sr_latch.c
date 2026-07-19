/*
NOR Gate SR Latch
In this configuration, the inputs are active HIGH:
S=1, R=0 (Set): The output Q goes to 1.
S=0, R=1 (Reset): The output Q goes to 0.
S=0, R=0 (Hold): The latch holds its previous state.
S=1, R=1 (Invalid): Both outputs attempt to go to 0, violating the complementary nature of Q and Qb). This is a forbidden state.

NAND Gate SR Latch
In a NAND implementation, the inputs are inverted (active LOW):
S=0, R=1 (Set): Output Q goes to 1.
S=1, R=0 (Reset): Output Q goes to 0.
S=1, R=1 (Hold): The latch holds its previous state.
S=0, R=0 (Invalid): Both outputs attempt to go to 1, which contradicts their intended inverse relationship.
*/

#include "../../include/sequential/sr_latch.h"
#include "../../include/gates/nor.h"

void srl_update(sr_latch* srl) {
  nor_t n0, n1;

  n0.in1 = srl->R;
  n0.in2 = srl->Qb;
  n0.out = srl->Q;

  n1.in1 = srl->Q;
  n1.in2 = srl->S;
  n1.out = srl->Qb;

  nor_update(&n0);
  nor_update(&n1);

  // We had to call these repeatedly, because to make the circuit stable. 
  // First two updates, Q and Qb, but updated Qb is not fed to first NOR gate.
  //  So we had to call them again, to make the circuit stable.
  nor_update(&n0);
  nor_update(&n1);
}