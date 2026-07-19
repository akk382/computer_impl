#include <stdio.h>

#include "../include/sequential/d_flipflop.h"
#include "../include/core/utils.h"

int main(void)
{
  wire_t D   = { LOW };
  wire_t CLK = { LOW };

  /*
   * These are initialized only to give the simulator a known
   * starting state. Do not modify them during the test.
   */
  wire_t Qm  = { LOW };
  wire_t Qmb = { HIGH };
  wire_t Q   = { LOW };
  wire_t Qb  = { HIGH };

  d_flipflop dff = {
    .D   = &D,
    .CLK = &CLK,
    .Qm  = &Qm,
    .Qmb = &Qmb,
    .Q   = &Q,
    .Qb  = &Qb
};

  /* Step 1: Clock LOW, data LOW. */
  CLK.val = LOW;
  D.val = LOW;
  dff_update(&dff);

  printf(
      "CLK=LOW,  D=LOW  -> Q=%s, Qm=%s\n",
      signal_to_string(Q.val),
      signal_to_string(Qm.val)
  );

  /* Step 2: Clock remains LOW. Master should follow D. */
  D.val = HIGH;
  dff_update(&dff);

  printf(
      "CLK=LOW,  D=HIGH -> Q=%s, Qm=%s\n",
      signal_to_string(Q.val),
      signal_to_string(Qm.val)
  );

  /* Step 3: Rising edge. Slave should capture master's HIGH. */
  CLK.val = HIGH;
  dff_update(&dff);

  printf(
      "CLK=HIGH, D=HIGH -> Q=%s, Qm=%s\n",
      signal_to_string(Q.val),
      signal_to_string(Qm.val)
  );

  /* Step 4: Change D while clock remains HIGH. Q must hold HIGH. */
  D.val = LOW;
  dff_update(&dff);

  printf(
      "CLK=HIGH, D=LOW  -> Q=%s, Qm=%s\n",
      signal_to_string(Q.val),
      signal_to_string(Qm.val)
  );

  /* Step 5: Falling edge. Q should still hold HIGH. */
  CLK.val = LOW;
  dff_update(&dff);

  printf(
      "CLK=LOW,  D=LOW  -> Q=%s, Qm=%s\n",
      signal_to_string(Q.val),
      signal_to_string(Qm.val)
  );

  /* Step 6: Next rising edge. Slave should capture master's LOW. */
  CLK.val = HIGH;
  dff_update(&dff);

  printf(
      "CLK=HIGH, D=LOW  -> Q=%s, Qm=%s\n",
      signal_to_string(Q.val),
      signal_to_string(Qm.val)
  );

  return 0;
}
