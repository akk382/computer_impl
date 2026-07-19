#include "../../include/sequential/four_bit_reg.h"
#include "../../include/sequential/one_bit_reg.h"

void fbr_update(four_bit_reg* fbr) {
  one_bit_reg obr0, obr1, obr2, obr3;

  obr0.LOAD = obr1.LOAD = obr2.LOAD = obr3.LOAD = fbr->LOAD;
  obr0.CLK = obr1.CLK = obr2.CLK = obr3.CLK = fbr->CLK;

  obr0.D = fbr->D.bit0;
  obr1.D = fbr->D.bit1;
  obr2.D = fbr->D.bit2;
  obr3.D = fbr->D.bit3;

  obr0.Qm = fbr->Qm.bit0;
  obr1.Qm = fbr->Qm.bit1;
  obr2.Qm = fbr->Qm.bit2;
  obr3.Qm = fbr->Qm.bit3;

  obr0.Qmb = fbr->Qmb.bit0;
  obr1.Qmb = fbr->Qmb.bit1;
  obr2.Qmb = fbr->Qmb.bit2;
  obr3.Qmb = fbr->Qmb.bit3;

  obr0.Q = fbr->Q.bit0;
  obr1.Q = fbr->Q.bit1;
  obr2.Q = fbr->Q.bit2;
  obr3.Q = fbr->Q.bit3;

  obr0.Qb = fbr->Qb.bit0;
  obr1.Qb = fbr->Qb.bit1;
  obr2.Qb = fbr->Qb.bit2;
  obr3.Qb = fbr->Qb.bit3;

  obreg_update(&obr0);
  obreg_update(&obr1);
  obreg_update(&obr2);
  obreg_update(&obr3);
}