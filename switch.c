#include "switch.h"

inline void switch_update(switch_t* sw) {
  if (sw->input->val == HIGH) {
    if (sw->control->val == HIGH) sw->output->val = HIGH;
    else sw->output->val = FLOATING;
  } else {
    if (sw->control->val == LOW) sw->output->val = FLOATING;
    else sw->output->val = LOW;
  }
}