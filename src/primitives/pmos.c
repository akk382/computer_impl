#include "../../include/primitives/pmos.h"

void pmos_update_old(pmos_old_t* sw) {
  if (sw->control->val == HIGH) sw->output->val = FLOATING;
  else sw->output->val = HIGH;
}

// We had to define this because, the source can be FLOATING when connected in series.
void pmos_update(pmos_t* sw) {
  if (sw->source->val == HIGH) {
    if (sw->gate->val == HIGH) {
      sw->drain->val = FLOATING;
    } else {
      sw->drain->val = HIGH;
    }
  } else {
    sw->drain->val = FLOATING;
  }
}