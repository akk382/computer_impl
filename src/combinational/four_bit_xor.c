#include "../../include/combinational/four_bit_xor.h"
#include "../../include/gates/xor.h"

void fbx_update(four_bit_xor* fbx) {
  xor_t xr0, xr1, xr2, xr3;

  xr0.in1 = fbx->in1.bit0;
  xr0.in2 = fbx->in2.bit0;
  xr0.out = fbx->out.bit0;

  xr1.in1 = fbx->in1.bit1;
  xr1.in2 = fbx->in2.bit1;
  xr1.out = fbx->out.bit1;

  xr2.in1 = fbx->in1.bit2;
  xr2.in2 = fbx->in2.bit2;
  xr2.out = fbx->out.bit2;

  xr3.in1 = fbx->in1.bit3;
  xr3.in2 = fbx->in2.bit3;
  xr3.out = fbx->out.bit3;

  xor_update(&xr0);
  xor_update(&xr1);
  xor_update(&xr2);
  xor_update(&xr3);
}