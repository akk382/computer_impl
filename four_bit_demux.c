#include "four_bit_demux.h"
#include "demux.h"

void fbd_update(four_bit_demux* fbd) {
  demux_t dm0, dm1, dm2, dm3;

  dm0.in = fbd->in.bit0;
  dm0.out0 = fbd->out0.bit0;
  dm0.out1 = fbd->out1.bit0;

  dm1.in = fbd->in.bit1;
  dm1.out0 = fbd->out0.bit1;
  dm1.out1 = fbd->out1.bit1;
  
  dm2.in = fbd->in.bit2;
  dm2.out0 = fbd->out0.bit2;
  dm2.out1 = fbd->out1.bit2;
  
  dm3.in = fbd->in.bit3;
  dm3.out0 = fbd->out0.bit3;
  dm3.out1 = fbd->out1.bit3;

  dm0.sel = dm1.sel = dm2.sel = dm3.sel = fbd->sel;

  demux_update(&dm0);
  demux_update(&dm1);
  demux_update(&dm2);
  demux_update(&dm3);
}