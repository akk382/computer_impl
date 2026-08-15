#include "../../include/combinational/four_bit_or.h"

#include "../../include/gates/or.h"

void four_bit_or_update(const four_bit_or_t* fbor)
{
  or_t or0, or1, or2, or3;

  or0.in1 = fbor->in0.bit0;
  or0.in2 = fbor->in1.bit0;
  or0.out = fbor->out.bit0;

  or1.in1 = fbor->in0.bit1;
  or1.in2 = fbor->in1.bit1;
  or1.out = fbor->out.bit1;

  or2.in1 = fbor->in0.bit2;
  or2.in2 = fbor->in1.bit2;
  or2.out = fbor->out.bit2;

  or3.in1 = fbor->in0.bit3;
  or3.in2 = fbor->in1.bit3;
  or3.out = fbor->out.bit3;

  or_update(&or0);
  or_update(&or1);
  or_update(&or2);
  or_update(&or3);
}
