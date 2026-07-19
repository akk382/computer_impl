#include "../../include/sequential/gated_sr_latch.h"
#include "../../include/sequential/sr_latch.h"
#include "../../include/gates/and.h"

void gsrl_update(const gated_sr_latch_t* gsrl) {
  and_t and0, and1;

  wire_t srl_S, srl_R;

  sr_latch srl = {.S = &srl_S, .R = &srl_R};

  and0.in1 = gsrl->S;
  and0.in2 = gsrl->E;
  and0.out = srl.S;

  and1.in1 = gsrl->E;
  and1.in2 = gsrl->R;
  and1.out = srl.R;

  srl.Q = gsrl->Q;
  srl.Qb = gsrl->Qb;

  and_update(&and0);
  and_update(&and1);
  srl_update(&srl);
}