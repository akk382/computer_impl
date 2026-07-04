#include "nmos.h"

void nmos_update_old(nmos_old_t* sw) {
  if (sw->control->val == LOW) sw->output->val = FLOATING;
  else sw->output->val = LOW;
}

void nmos_update(nmos_t* sw) {
  if (sw->source->val == LOW) {
    if (sw->gate->val == HIGH) {
      sw->drain->val = LOW;
    } else {
      sw->drain->val = FLOATING;
    }
  } else {
    sw->drain->val = FLOATING;
  }
}