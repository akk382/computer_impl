#include "../../include/combinational/four_bit_adder.h"
#include "../../include/combinational/half_adder.h"
#include "../../include/combinational/full_adder.h"

void fba_update(four_bit_adder* fba) {
  half_adder ha;
  full_adder fa1, fa2, fa3;
  wire_t ha_carry, fa1_carry, fa2_carry;

  ha.in1 = fba->in1.bit0;
  ha.in2 = fba->in2.bit0;
  ha.carry = &ha_carry;
  ha.sum = fba->sum.bit0;

  fa1.c_in = ha.carry;
  fa1.in1 = fba->in1.bit1;
  fa1.in2 = fba->in2.bit1;
  fa1.sum = fba->sum.bit1;
  fa1.c_out = &fa1_carry;

  fa2.c_in = fa1.c_out;
  fa2.in1 = fba->in1.bit2;
  fa2.in2 = fba->in2.bit2;
  fa2.sum = fba->sum.bit2;
  fa2.c_out = &fa2_carry;

  fa3.c_in = fa2.c_out;
  fa3.in1 = fba->in1.bit3;
  fa3.in2 = fba->in2.bit3;
  fa3.sum = fba->sum.bit3;
  fa3.c_out = fba->carry;

  ha_update(&ha);
  fa_update(&fa1);
  fa_update(&fa2);
  fa_update(&fa3);
}