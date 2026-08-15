#include <stdio.h>

#include "bus/three_driver_bus_resolver.h"
#include "core/utils.h"

static void print_nibble(const char *name, const nibble *n)
{
    printf(
        "%s=%s %s %s %s",
        name,
        signal_to_string(n->bit3->val),
        signal_to_string(n->bit2->val),
        signal_to_string(n->bit1->val),
        signal_to_string(n->bit0->val)
    );
}

static void run_case(
    const char *label,

    signal_t d0_3, signal_t d0_2, signal_t d0_1, signal_t d0_0,
    signal_t d1_3, signal_t d1_2, signal_t d1_1, signal_t d1_0,
    signal_t d2_3, signal_t d2_2, signal_t d2_1, signal_t d2_0
)
{
    wire_t d0_b0 = { d0_0 };
    wire_t d0_b1 = { d0_1 };
    wire_t d0_b2 = { d0_2 };
    wire_t d0_b3 = { d0_3 };

    wire_t d1_b0 = { d1_0 };
    wire_t d1_b1 = { d1_1 };
    wire_t d1_b2 = { d1_2 };
    wire_t d1_b3 = { d1_3 };

    wire_t d2_b0 = { d2_0 };
    wire_t d2_b1 = { d2_1 };
    wire_t d2_b2 = { d2_2 };
    wire_t d2_b3 = { d2_3 };

    wire_t bus0 = { FLOATING };
    wire_t bus1 = { FLOATING };
    wire_t bus2 = { FLOATING };
    wire_t bus3 = { FLOATING };

    three_driver_bus_resolver_t resolver = {
        .driver0 = { &d0_b0, &d0_b1, &d0_b2, &d0_b3 },
        .driver1 = { &d1_b0, &d1_b1, &d1_b2, &d1_b3 },
        .driver2 = { &d2_b0, &d2_b1, &d2_b2, &d2_b3 },
        .bus = { &bus0, &bus1, &bus2, &bus3 }
    };

    three_driver_bus_resolver_update(&resolver);

    printf("%-28s ", label);

    print_nibble("D0", &resolver.driver0);
    printf(" | ");

    print_nibble("D1", &resolver.driver1);
    printf(" | ");

    print_nibble("D2", &resolver.driver2);
    printf(" | ");

    print_nibble("BUS", &resolver.bus);
    printf("\n");
}

int main(void)
{
    /*
     * Case 1:
     * Nobody drives the bus.
     */
    run_case(
        "all floating",
        FLOATING, FLOATING, FLOATING, FLOATING,
        FLOATING, FLOATING, FLOATING, FLOATING,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    /*
     * Case 2:
     * Only driver0 drives 1010.
     */
    run_case(
        "only D0 drives 1010",
        HIGH, LOW, HIGH, LOW,
        FLOATING, FLOATING, FLOATING, FLOATING,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    /*
     * Case 3:
     * Only driver1 drives 0101.
     */
    run_case(
        "only D1 drives 0101",
        FLOATING, FLOATING, FLOATING, FLOATING,
        LOW, HIGH, LOW, HIGH,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    /*
     * Case 4:
     * Only driver2 drives 1111.
     */
    run_case(
        "only D2 drives 1111",
        FLOATING, FLOATING, FLOATING, FLOATING,
        FLOATING, FLOATING, FLOATING, FLOATING,
        HIGH, HIGH, HIGH, HIGH
    );

    /*
     * Case 5:
     * D0 and D1 drive the same value.
     * This is electrically valid.
     */
    run_case(
        "D0 D1 same 1010",
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    /*
     * Case 6:
     * D0 and D2 drive the same value.
     * This is also electrically valid.
     */
    run_case(
        "D0 D2 same 1010",
        HIGH, LOW, HIGH, LOW,
        FLOATING, FLOATING, FLOATING, FLOATING,
        HIGH, LOW, HIGH, LOW
    );

    /*
     * Case 7:
     * All three drive the same value.
     * Still valid.
     */
    run_case(
        "all same 1010",
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW
    );

    /*
     * Case 8:
     * D0 and D1 disagree on every bit.
     */
    run_case(
        "D0 D1 conflict",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    /*
     * Case 9:
     * D0 and D2 disagree on every bit.
     */
    run_case(
        "D0 D2 conflict",
        HIGH, LOW, HIGH, LOW,
        FLOATING, FLOATING, FLOATING, FLOATING,
        LOW, HIGH, LOW, HIGH
    );

    /*
     * Case 10:
     * D1 and D2 disagree on every bit.
     */
    run_case(
        "D1 D2 conflict",
        FLOATING, FLOATING, FLOATING, FLOATING,
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH
    );

    /*
     * Case 11:
     * Partial conflict.
     *
     * D0 = 1010
     * D1 = floating
     * D2 = 1001
     *
     * bit3: HIGH + HIGH -> HIGH
     * bit2: LOW  + LOW  -> LOW
     * bit1: HIGH + LOW  -> CONFLICT
     * bit0: LOW  + HIGH -> CONFLICT
     */
    run_case(
        "partial conflict",
        HIGH, LOW, HIGH, LOW,
        FLOATING, FLOATING, FLOATING, FLOATING,
        HIGH, LOW, LOW, HIGH
    );

    /*
     * Case 12:
     * Conflict created early:
     * D0 and D1 conflict, then D2 floats.
     */
    run_case(
        "early conflict",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    /*
     * Case 13:
     * Conflict created after first resolver:
     * D0 and D1 agree, then D2 disagrees.
     */
    run_case(
        "late conflict",
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH
    );

    return 0;
}