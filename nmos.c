#include "nmos.h"

void nmos_update(nmos_t* sw) {
  if (sw->control->val == LOW) sw->output->val = FLOATING;
  else sw->output->val = LOW;
}