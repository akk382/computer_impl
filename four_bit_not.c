#include "four_bit_not.h"
#include "not.h"

void fbn_update(four_bit_not* fbn) {
  not_t n0, n1, n2, n3;

  n0.in = fbn->in.bit0;
  n1.in = fbn->in.bit1;
  n2.in = fbn->in.bit2;
  n3.in = fbn->in.bit3;

  n0.out = fbn->out.bit0;
  n1.out = fbn->out.bit1;
  n2.out = fbn->out.bit2;
  n3.out = fbn->out.bit3;

  not_update(&n0);
  not_update(&n1);
  not_update(&n2);
  not_update(&n3);
}