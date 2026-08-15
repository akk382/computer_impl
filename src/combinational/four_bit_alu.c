#include "../../include/combinational/four_bit_alu.h"

#include "../../include/combinational/four_bit_adder.h"
#include "../../include/combinational/four_bit_and.h"
#include "../../include/combinational/four_bit_or.h"
#include "../../include/combinational/four_to_one_mux.h"
#include "../../include/combinational/four_bit_sub.h"

void four_bit_alu_update(const four_bit_alu_t* fbalu)
{
  four_to_one_mux mux0, mux1, mux2, mux3;
  four_bit_adder fbadd;
  four_bit_sub fbsub;
  four_bit_and fband;
  four_bit_or_t fbor;

  wire_t add0 = { FLOATING }, add1 = { FLOATING }, add2 = { FLOATING }, add3 = { FLOATING };
  wire_t sub0 = { FLOATING }, sub1 = { FLOATING }, sub2 = { FLOATING }, sub3 = { FLOATING };
  wire_t and0 = { FLOATING }, and1 = { FLOATING }, and2 = { FLOATING }, and3 = { FLOATING };
  wire_t or0 = { FLOATING }, or1 = { FLOATING }, or2 = { FLOATING }, or3 = { FLOATING };

  nibble add_out = { &add0, &add1, &add2, &add3 };
  nibble sub_out = { &sub0, &sub1, &sub2, &sub3 };
  nibble and_out = { &and0, &and1, &and2, &and3 };
  nibble or_out = { &or0, &or1, &or2, &or3 };

  fbadd.in1 = fbalu->in0;
  fbadd.in2 = fbalu->in1;
  fbadd.sum = add_out;
  fbadd.carry = fbalu->carry;

  fbsub.in1 = fbalu->in0;
  fbsub.in2 = fbalu->in1;
  fbsub.out = sub_out;

  fband.in1 = fbalu->in0;
  fband.in2 = fbalu->in1;
  fband.out = and_out;

  fbor.in0 = fbalu->in0;
  fbor.in1 = fbalu->in1;
  fbor.out = or_out;

  mux0.in0 = fbadd.sum.bit0;
  mux0.in1 = fbsub.out.bit0;
  mux0.in2 = fband.out.bit0;
  mux0.in3 = fbor.out.bit0;
  mux0.sel0 = fbalu->sel0;
  mux0.sel1 = fbalu->sel1;
  mux0.out = fbalu->out.bit0;

  mux1.in0 = fbadd.sum.bit1;
  mux1.in1 = fbsub.out.bit1;
  mux1.in2 = fband.out.bit1;
  mux1.in3 = fbor.out.bit1;
  mux1.sel0 = fbalu->sel0;
  mux1.sel1 = fbalu->sel1;
  mux1.out = fbalu->out.bit1;

  mux2.in0 = fbadd.sum.bit2;
  mux2.in1 = fbsub.out.bit2;
  mux2.in2 = fband.out.bit2;
  mux2.in3 = fbor.out.bit2;
  mux2.sel0 = fbalu->sel0;
  mux2.sel1 = fbalu->sel1;
  mux2.out = fbalu->out.bit2;

  mux3.in0 = fbadd.sum.bit3;
  mux3.in1 = fbsub.out.bit3;
  mux3.in2 = fband.out.bit3;
  mux3.in3 = fbor.out.bit3;
  mux3.sel0 = fbalu->sel0;
  mux3.sel1 = fbalu->sel1;
  mux3.out = fbalu->out.bit3;

  fba_update(&fbadd);
  fbs_update(&fbsub);
  four_bit_and_update(&fband);
  four_bit_or_update(&fbor);
  fto_mux_update(&mux0);
  fto_mux_update(&mux1);
  fto_mux_update(&mux2);
  fto_mux_update(&mux3);
}
