#include "../../include/combinational/half_adder.h"
#include "../../include/gates/xor.h"
#include "../../include/gates/and.h"

void ha_update(half_adder* ha) {
  and_t carry;
  xor_t sum;

  sum.in1 = ha->in1;
  sum.in2 = ha->in2;
  sum.out = ha->sum;

  carry.in1 = ha->in1;
  carry.in2 = ha->in2;
  carry.out = ha->carry;

  xor_update(&sum);
  and_update(&carry);
}