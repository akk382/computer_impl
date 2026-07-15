#include <stdio.h>

#include "bus_conflict_resolver.h"
#include "utils.h"

static void test_case(signal_t d0_val, signal_t d1_val)
{
  wire_t driver0 = { d0_val };
  wire_t driver1 = { d1_val };
  wire_t bus = { FLOATING };

  bus_conflict_resolver_t bcr = {
    .driver0 = &driver0,
    .driver1 = &driver1,
    .bus = &bus
};

  bcr_update(&bcr);

  printf(
      "%-8s + %-8s -> %s\n",
      signal_to_string(driver0.val),
      signal_to_string(driver1.val),
      signal_to_string(bus.val)
  );
}

int main(void)
{
  test_case(FLOATING, FLOATING);

  test_case(HIGH, FLOATING);
  test_case(LOW, FLOATING);

  test_case(FLOATING, HIGH);
  test_case(FLOATING, LOW);

  test_case(HIGH, HIGH);
  test_case(LOW, LOW);

  test_case(HIGH, LOW);
  test_case(LOW, HIGH);

  return 0;
}