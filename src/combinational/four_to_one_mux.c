#include "../../include/combinational/four_to_one_mux.h"
#include "../../include/combinational/mux.h"
#include "../../include/core/wire.h"

void fto_mux_update(four_to_one_mux* ftom) {
  mux_t m0, m1, m2;

  wire_t m0_out, m1_out;

  m0.in0 = ftom->in0;
  m0.in1 = ftom->in1;
  m0.sel = ftom->sel0;
  m0.out = &m0_out;
  
  m1.in0 = ftom->in2;
  m1.in1 = ftom->in3;
  m1.sel = ftom->sel0;
  m1.out = &m1_out;
  
  m2.in0 = m0.out;
  m2.in1 = m1.out;
  m2.sel = ftom->sel1;
  m2.out = ftom->out;

  obm_update(&m0);
  obm_update(&m1);
  obm_update(&m2);
}