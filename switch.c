#include "switch.h"

/* switch
 * INPUT = HIGH, CONTROL = HIGH -> OUTPUT = HIGH
 * INPUT = HIGH, CONTROL = LOW -> OUTPUT = FLOATING
 * INPUT = LOW, CONTROL = HIGH -> OUTPUT = LOW
 * INPUT = LOW, CONTROL = LOW -> OUTPUT = FLOATING
 * INPUT = FLOATING, CONTROL = HIGH -> OUTPUT = FLOATING
 * INPUT = FLOATING, CONTROL = LOW -> OUTPUT = FLOATING
 *
 * From the above Truth Table, we can observe that:
 * when the CONTROL = HIGH, output = input.
 * Else output = FLOATING.
 */

void switch_update(const switch_t* sw) {
  if (sw->control->val == HIGH) {
    sw->output->val = sw->input->val;
  } else {
    sw->output->val = FLOATING;
  }
}