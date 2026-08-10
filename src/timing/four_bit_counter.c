#include "../../include/timing/four_bit_counter.h"
#include "../../include/sequential/four_bit_reg.h"
#include "../../include/combinational/four_bit_inc.h"
#include "../../include/combinational/four_bit_mux.h"

void four_bit_counter_update(four_bit_counter_t *cntr)
{
  four_bit_reg fbr;
  four_bit_inc fbi;
  four_bit_mux en_mux;
  four_bit_mux rst_mux;

  wire_t load = { HIGH };

  wire_t fbrd0 = { FLOATING };
  wire_t fbrd1 = { FLOATING };
  wire_t fbrd2 = { FLOATING };
  wire_t fbrd3 = { FLOATING };

  wire_t enout0 = { FLOATING };
  wire_t enout1 = { FLOATING };
  wire_t enout2 = { FLOATING };
  wire_t enout3 = { FLOATING };

  wire_t fbiout0 = { FLOATING };
  wire_t fbiout1 = { FLOATING };
  wire_t fbiout2 = { FLOATING };
  wire_t fbiout3 = { FLOATING };

  wire_t carry = { FLOATING };

  wire_t zero0 = { LOW };
  wire_t zero1 = { LOW };
  wire_t zero2 = { LOW };
  wire_t zero3 = { LOW };

  nibble fbr_D = { &fbrd0, &fbrd1, &fbrd2, &fbrd3 };
  nibble en_out = { &enout0, &enout1, &enout2, &enout3 };
  nibble fbi_out = { &fbiout0, &fbiout1, &fbiout2, &fbiout3 };
  nibble zero = { &zero0, &zero1, &zero2, &zero3 };

  nibble fbr_Qm = { &cntr->qm0, &cntr->qm1, &cntr->qm2, &cntr->qm3 };
  nibble fbr_Qmb = { &cntr->qmb0, &cntr->qmb1, &cntr->qmb2, &cntr->qmb3 };
  nibble fbr_Qb = { &cntr->qb0, &cntr->qb1, &cntr->qb2, &cntr->qb3 };

  fbi.in = cntr->out;
  fbi.carry = &carry;
  fbi.out = fbi_out;

  en_mux.in0 = cntr->out;
  en_mux.in1 = fbi_out;
  en_mux.sel = cntr->EN;
  en_mux.out = en_out;

  rst_mux.in0 = en_out;
  rst_mux.in1 = zero;
  rst_mux.sel = cntr->RST;
  rst_mux.out = fbr_D;

  fbr.CLK = cntr->CLK;
  fbr.LOAD = &load;
  fbr.D = fbr_D;
  fbr.Qm = fbr_Qm;
  fbr.Qmb = fbr_Qmb;
  fbr.Q = cntr->out;
  fbr.Qb = fbr_Qb;

  fbi_update(&fbi);
  fbm_update(&en_mux);
  fbm_update(&rst_mux);
  fbr_update(&fbr);
}