#include "../../include/primitives/nmos_net.h"

void nmos_series_update(nmos_net* nm) {
  nm->n1->source = nm->n2->drain;
  nmos_update(nm->n2);
  nmos_update(nm->n1);
  nm->drain->val = nm->n1->drain->val;
}

void nmos_parallel_update(nmos_net* nm) {
  nmos_update(nm->n1);
  nmos_update(nm->n2);

  if (nm->n1->drain->val == LOW) {
    nm->drain->val = LOW;
  } else if (nm->n2->drain->val == LOW) {
    nm->drain->val = LOW;
  } else {
    nm->drain->val = FLOATING;
  }
}