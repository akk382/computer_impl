#include "pmos.h"

void pmos_update(pmos_t* sw) {
  if (sw->control->val == HIGH) sw->output->val = FLOATING;
  else sw->output->val = HIGH;
}