#include "../../include/combinational/four_bit_and.h"

#include "gates/and.h"

void four_bit_and_update(const four_bit_and* fband)
{
  and_t and0, and1, and2, and3;

  and0.in1 = fband->in1.bit0;
  and0.in2 = fband->in2.bit0;
  and0.out = fband->out.bit0;

  and1.in1 = fband->in1.bit1;
  and1.in2 = fband->in2.bit1;
  and1.out = fband->out.bit1;

  and2.in1 = fband->in1.bit2;
  and2.in2 = fband->in2.bit2;
  and2.out = fband->out.bit2;

  and3.in1 = fband->in1.bit3;
  and3.in2 = fband->in2.bit3;
  and3.out = fband->out.bit3;

  and_update(&and0);
  and_update(&and1);
  and_update(&and2);
  and_update(&and3);
}
