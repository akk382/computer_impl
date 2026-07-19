#include "../../include/sequential/d_latch.h"
#include "../../include/core/wire.h"
#include "../../include/sequential/gated_sr_latch.h"
#include "../../include/gates/not.h"

void dl_update(const d_latch* dl) {
  not_t n;

  wire_t srl_R;

  gated_sr_latch_t gsrl = {.R = &srl_R};

  n.in = dl->D;
  n.out = gsrl.R;

  gsrl.E = dl->E;
  gsrl.S = dl->D;
  gsrl.Q = dl->Q;
  gsrl.Qb = dl->Qb;

  not_update(&n);
  gsrl_update(&gsrl);
}