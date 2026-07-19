#include "../include/sequential/d_latch.h"
#include "../include/core/utils.h"
#include <stdio.h>

int main(void)
{
  wire_t E = { LOW };
  wire_t D = { LOW };
  wire_t Q = { LOW };
  wire_t Qb = { HIGH };

  d_latch dl = {
    .E = &E,
    .D = &D,
    .Q = &Q,
    .Qb = &Qb
};

  /* Establish a known initial state electronically. */
  E.val = HIGH;
  D.val = LOW;
  dl_update(&dl);

  /* 1. Disabled: hold LOW. */
  E.val = LOW;
  D.val = LOW;
  dl_update(&dl);
  printf("E=LOW, D=LOW  -> Q=%s\n",
         signal_to_string(dl.Q->val));

  /* 2. Enabled with D LOW. */
  E.val = HIGH;
  D.val = LOW;
  dl_update(&dl);
  printf("E=HIGH, D=LOW -> Q=%s\n",
         signal_to_string(dl.Q->val));

  /* 3. Enabled: Q follows D to HIGH. */
  D.val = HIGH;
  dl_update(&dl);
  printf("E=HIGH, D=HIGH -> Q=%s\n",
         signal_to_string(dl.Q->val));

  /* 4. Still enabled: Q follows D back to LOW. */
  D.val = LOW;
  dl_update(&dl);
  printf("E=HIGH, D=LOW -> Q=%s\n",
         signal_to_string(dl.Q->val));

  /* 5. Disabled: D changes, but Q holds LOW. */
  E.val = LOW;
  D.val = HIGH;
  dl_update(&dl);
  printf("E=LOW, D=HIGH -> Q=%s\n",
         signal_to_string(dl.Q->val));

  return 0;
}