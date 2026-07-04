#include "cmos.h"

void cmos_update(cmos_t* cm) {
  pmos_t pm;
  nmos_t nm;
  wire_t pm_output, nm_output;

  pm.control = nm.control = cm->control;
  pm.output = &pm_output;
  nm.output = &nm_output;

  nmos_update(&nm);
  pmos_update(&pm);

  if (pm_output.val == HIGH) {
    if (nm_output.val == FLOATING) {
      cm->output->val = HIGH;
    } else { // nm_output.val == LOW
      cm->output->val = CONFLICT; // impossible scenario
    }
  } else {  // pm_output.val == FLOATING
    if (nm_output.val == FLOATING) {
      cm->output->val = FLOATING; // imposible scenario
    } else {
      cm->output->val = LOW;
    }
  }
}