#include "../../include/primitives/pmos_net.h"

void pmos_series_update(pmos_net* pm) {
  pm->p2->source = pm->p1->drain;
  pmos_update(pm->p1);
  pmos_update(pm->p2);
  pm->drain->val = pm->p2->drain->val;
}

void pmos_parallel_update(pmos_net* pm) {
  pmos_update(pm->p1);
  pmos_update(pm->p2);

  if (pm->p1->drain->val == HIGH) {
    pm->drain->val = HIGH;
  } else if (pm->p2->drain->val == HIGH) {
    pm->drain->val = HIGH;
  } else {
    pm->drain->val = FLOATING;
  }
}