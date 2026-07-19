#include "../../include/combinational/two_bit_adder.h"
#include "../../include/combinational/half_adder.h"
#include "../../include/combinational/full_adder.h"

void tba_update(two_bit_adder* tba) {
  half_adder ha;
  full_adder fa;

  wire_t ha_carry;

  ha.in1 = tba->in1.bit0;
  ha.in2 = tba->in2.bit0;
  ha.sum = tba->sum.bit0;
  ha.carry = &ha_carry;

  fa.in1 = tba->in1.bit1;
  fa.in2 = tba->in2.bit1;
  fa.c_in = ha.carry;
  fa.sum = tba->sum.bit1;
  fa.c_out = tba->carry;

  ha_update(&ha);
  fa_update(&fa);
}