#include <stdio.h>

#include "../include/bus/four_bit_oe_buffer.h"
#include "../include/core/utils.h"

static void print_nibble(const char *name, const nibble *n)
{
  printf(
      "%s=%s%s%s%s",
      name,
      signal_to_string(n->bit3->val),
      signal_to_string(n->bit2->val),
      signal_to_string(n->bit1->val),
      signal_to_string(n->bit0->val)
  );
}

static void print_state(const char *label, const four_bit_oe_buffer_t *buf)
{
  printf("%-24s ", label);
  print_nibble("Q", &buf->Q);
  printf(" OE=%s ", signal_to_string(buf->OE->val));
  print_nibble("BUS", &buf->bus);
  printf("\n");
}

int main(void)
{
  wire_t oe = { LOW };

  wire_t q0 = { LOW };
  wire_t q1 = { HIGH };
  wire_t q2 = { LOW };
  wire_t q3 = { HIGH };

  wire_t bus0 = { FLOATING };
  wire_t bus1 = { FLOATING };
  wire_t bus2 = { FLOATING };
  wire_t bus3 = { FLOATING };

  four_bit_oe_buffer_t buf = {
    .Q = { &q0, &q1, &q2, &q3 },
    .OE = &oe,
    .bus = { &bus0, &bus1, &bus2, &bus3 }
  };

  /* Q = 1010, OE = LOW -> BUS = FLOATING */
  oe.val = LOW;
  fboeb_update(&buf);
  print_state("1010 disabled", &buf);

  /* Q = 1010, OE = HIGH -> BUS = 1010 */
  oe.val = HIGH;
  fboeb_update(&buf);
  print_state("1010 enabled", &buf);

  /* Change Q to 0101 while OE = HIGH -> BUS = 0101 */
  q3.val = LOW;
  q2.val = HIGH;
  q1.val = LOW;
  q0.val = HIGH;

  fboeb_update(&buf);
  print_state("0101 enabled", &buf);

  /* OE = LOW -> BUS = FLOATING */
  oe.val = LOW;
  fboeb_update(&buf);
  print_state("0101 disabled", &buf);

  return 0;
}