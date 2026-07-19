#include "../../include/sequential/one_bit_reg.h"
#include "../../include/combinational/mux.h"
#include "../../include/sequential/d_flipflop.h"

void obreg_update(const one_bit_reg* obreg) {
  mux_t mux;
  d_flipflop df;
  wire_t mux_out;

  mux.in0 = obreg->Q;
  mux.in1 = obreg->D;
  mux.sel = obreg->LOAD;
  mux.out = &mux_out;

  df.D = mux.out;
  df.CLK = obreg->CLK;
  df.Qm = obreg->Qm;
  df.Qmb = obreg->Qmb;
  df.Q = obreg->Q;
  df.Qb = obreg->Qb;

  obm_update(&mux);
  dff_update(&df);
}