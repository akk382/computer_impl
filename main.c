#include "nmos.h"
#include "pmos.h"
#include "cmos.h"
#include "utils.h"
#include "wire.h"
#include <stdio.h>

int main() {
  // nmos_t nm;
  // wire_t control, output;
  // nm.control = &control;
  // nm.output = &output;
  // control.val = HIGH;
  // nmos_update(&nm);
  // printf("HIGH, %s\n", signal_to_string(nm.output->val));
  
  // control.val = LOW;
  // nmos_update(&nm);
  // printf("LOW, %s\n", signal_to_string(nm.output->val));

  // pmos_t pm;
  // wire_t control, output;
  // pm.control = &control;
  // pm.output = &output;
  // control.val = HIGH;
  // pmos_update(&pm);
  // printf("HIGH, %s\n", signal_to_string(pm.output->val));
  
  // control.val = LOW;
  // pmos_update(&pm);
  // printf("LOW, %s\n", signal_to_string(pm.output->val));
  
  cmos_t cm;
  wire_t control;
  wire_t input, output;
  cm.control = &control;
  cm.output = &output;

  printf("CONTROL, OUTPUT\n");

  cm.control->val = LOW;
  cmos_update(&cm);
  printf("LOW, %s\n", signal_to_string(cm.output->val));

  cm.control->val = HIGH;
  cmos_update(&cm);
  printf("HIGH, %s\n", signal_to_string(cm.output->val));

  cm.control->val = FLOATING;
  cmos_update(&cm);
  printf("FLOATING, %s\n", signal_to_string(cm.output->val));
}