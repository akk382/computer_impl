#include "../../include/combinational/four_bit_mux.h"
#include "../../include/combinational/mux.h"

void fbm_update(four_bit_mux* fbm) {
  mux_t obm0, obm1, obm2, obm3;

  obm0.in0 = fbm->in0.bit0;
  obm0.in1 = fbm->in1.bit0;
  obm0.sel = fbm->sel;
  obm0.out = fbm->out.bit0;

  obm1.in0 = fbm->in0.bit1;
  obm1.in1 = fbm->in1.bit1;
  obm1.sel = fbm->sel;
  obm1.out = fbm->out.bit1;

  obm2.in0 = fbm->in0.bit2;
  obm2.in1 = fbm->in1.bit2;
  obm2.sel = fbm->sel;
  obm2.out = fbm->out.bit2;

  obm3.in0 = fbm->in0.bit3;
  obm3.in1 = fbm->in1.bit3;
  obm3.sel = fbm->sel;
  obm3.out = fbm->out.bit3;

  obm_update(&obm0);
  obm_update(&obm1);
  obm_update(&obm2);
  obm_update(&obm3);
}