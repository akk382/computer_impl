#include "cmos.h"

void cmos_update_old(cmos_t* cm) {
  pmos_old_t pm;
  nmos_old_t nm;
  wire_t pm_output, nm_output;

  pm.control = nm.control = cm->control;
  pm.output = &pm_output;
  nm.output = &nm_output;

  nmos_update_old(&nm);
  pmos_update_old(&pm);

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

void cmos_update(cmos_t* cm) {
  pmos_t pm;
  nmos_t nm;
  wire_t pm_output, nm_output;

  pm.gate = nm.gate = cm->control;
  pm.drain = &pm_output;
  nm.drain = &nm_output;

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