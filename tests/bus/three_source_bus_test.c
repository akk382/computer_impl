#include <stdio.h>

#include "bus/three_source_bus.h"
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

    signal_t s0_3, signal_t s0_2, signal_t s0_1, signal_t s0_0,
    signal_t s1_3, signal_t s1_2, signal_t s1_1, signal_t s1_0,
    signal_t s2_3, signal_t s2_2, signal_t s2_1, signal_t s2_0,

    signal_t oe0,
    signal_t oe1,
    signal_t oe2
)
{
    wire_t s0_b0 = { s0_0 };
    wire_t s0_b1 = { s0_1 };
    wire_t s0_b2 = { s0_2 };
    wire_t s0_b3 = { s0_3 };

    wire_t s1_b0 = { s1_0 };
    wire_t s1_b1 = { s1_1 };
    wire_t s1_b2 = { s1_2 };
    wire_t s1_b3 = { s1_3 };

    wire_t s2_b0 = { s2_0 };
    wire_t s2_b1 = { s2_1 };
    wire_t s2_b2 = { s2_2 };
    wire_t s2_b3 = { s2_3 };

    wire_t source0_oe = { oe0 };
    wire_t source1_oe = { oe1 };
    wire_t source2_oe = { oe2 };

    wire_t bus0 = { FLOATING };
    wire_t bus1 = { FLOATING };
    wire_t bus2 = { FLOATING };
    wire_t bus3 = { FLOATING };

    three_source_bus_t tsb = {
        .source0 = { &s0_b0, &s0_b1, &s0_b2, &s0_b3 },
        .source0_OE = &source0_oe,

        .source1 = { &s1_b0, &s1_b1, &s1_b2, &s1_b3 },
        .source1_OE = &source1_oe,

        .source2 = { &s2_b0, &s2_b1, &s2_b2, &s2_b3 },
        .source2_OE = &source2_oe,

        .bus = { &bus0, &bus1, &bus2, &bus3 }
    };

    three_source_bus_update(&tsb);

    printf("%-30s ", label);

    print_nibble("S0", &tsb.source0);
    printf(" OE0=%s | ", signal_to_string(source0_oe.val));

    print_nibble("S1", &tsb.source1);
    printf(" OE1=%s | ", signal_to_string(source1_oe.val));

    print_nibble("S2", &tsb.source2);
    printf(" OE2=%s | ", signal_to_string(source2_oe.val));

    print_nibble("BUS", &tsb.bus);
    printf("\n");
}

int main(void)
{
    /*
     * Case 1:
     * All OE disabled.
     * Even though sources have values, nobody should drive the bus.
     */
    run_case(
        "all OE disabled",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, HIGH, HIGH,
        LOW, LOW, LOW
    );

    /*
     * Case 2:
     * Only source0 drives 1010.
     */
    run_case(
        "only S0 drives 1010",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, HIGH, HIGH,
        HIGH, LOW, LOW
    );

    /*
     * Case 3:
     * Only source1 drives 0101.
     */
    run_case(
        "only S1 drives 0101",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, HIGH, HIGH,
        LOW, HIGH, LOW
    );

    /*
     * Case 4:
     * Only source2 drives 1111.
     */
    run_case(
        "only S2 drives 1111",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, HIGH, HIGH,
        LOW, LOW, HIGH
    );

    /*
     * Case 5:
     * S0 and S1 enabled with same value.
     * This is valid: same voltage from both drivers.
     */
    run_case(
        "S0 S1 same 1010",
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, LOW
    );

    /*
     * Case 6:
     * S0 and S2 enabled with same value.
     */
    run_case(
        "S0 S2 same 1010",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH
    );

    /*
     * Case 7:
     * All three enabled with same value.
     */
    run_case(
        "all same 1010",
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW,
        HIGH, HIGH, HIGH
    );

    /*
     * Case 8:
     * S0 and S1 enabled with opposite values.
     * Bus should become CONFLICT on every bit.
     */
    run_case(
        "S0 S1 conflict",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, HIGH, HIGH,
        HIGH, HIGH, LOW
    );

    /*
     * Case 9:
     * S0 and S2 enabled with opposite values.
     */
    run_case(
        "S0 S2 conflict",
        HIGH, LOW, HIGH, LOW,
        HIGH, HIGH, HIGH, HIGH,
        LOW, HIGH, LOW, HIGH,
        HIGH, LOW, HIGH
    );

    /*
     * Case 10:
     * S1 and S2 enabled with opposite values.
     */
    run_case(
        "S1 S2 conflict",
        HIGH, HIGH, HIGH, HIGH,
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        LOW, HIGH, HIGH
    );

    /*
     * Case 11:
     * Partial conflict.
     *
     * S0 = 1010
     * S2 = 1001
     *
     * bit3: HIGH + HIGH -> HIGH
     * bit2: LOW  + LOW  -> LOW
     * bit1: HIGH + LOW  -> CONFLICT
     * bit0: LOW  + HIGH -> CONFLICT
     */
    run_case(
        "partial conflict",
        HIGH, LOW, HIGH, LOW,
        LOW, LOW, LOW, LOW,
        HIGH, LOW, LOW, HIGH,
        HIGH, LOW, HIGH
    );

    /*
     * Case 12:
     * Conflict from S0/S1, S2 disabled.
     * Proves conflict propagates through internal resolver path.
     */
    run_case(
        "early conflict",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, HIGH, HIGH,
        HIGH, HIGH, LOW
    );

    /*
     * Case 13:
     * S0/S1 agree, then S2 disagrees.
     * Proves late conflict is detected.
     */
    run_case(
        "late conflict",
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH, HIGH
    );

    /*
     * Case 14:
     * Change source values do not matter when OE is LOW.
     * S0 has 1111, S1 has 0000, S2 has 1010,
     * but all OE are LOW, so BUS must be FLOATING.
     */
    run_case(
        "values ignored when OE low",
        HIGH, HIGH, HIGH, HIGH,
        LOW, LOW, LOW, LOW,
        HIGH, LOW, HIGH, LOW,
        LOW, LOW, LOW
    );

    return 0;
}