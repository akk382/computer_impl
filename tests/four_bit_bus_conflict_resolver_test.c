#include <stdio.h>

#include "../include/bus/four_bit_bus_conflict_resolver.h"
#include "../include/core/utils.h"

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
    signal_t d1_3, signal_t d1_2, signal_t d1_1, signal_t d1_0
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

    wire_t bus0 = { FLOATING };
    wire_t bus1 = { FLOATING };
    wire_t bus2 = { FLOATING };
    wire_t bus3 = { FLOATING };

    four_bit_bus_conflict_resolver_t resolver = {
        .driver0 = { &d0_b0, &d0_b1, &d0_b2, &d0_b3 },
        .driver1 = { &d1_b0, &d1_b1, &d1_b2, &d1_b3 },
        .bus = { &bus0, &bus1, &bus2, &bus3 }
    };

    fbbcr_update(&resolver);

    printf("%-24s ", label);
    print_nibble("D0", &resolver.driver0);
    printf(" | ");
    print_nibble("D1", &resolver.driver1);
    printf(" | ");
    print_nibble("BUS", &resolver.bus);
    printf("\n");
}

int main(void)
{
    run_case(
        "both floating",
        FLOATING, FLOATING, FLOATING, FLOATING,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    run_case(
        "driver0 drives 1010",
        HIGH, LOW, HIGH, LOW,
        FLOATING, FLOATING, FLOATING, FLOATING
    );

    run_case(
        "driver1 drives 0101",
        FLOATING, FLOATING, FLOATING, FLOATING,
        LOW, HIGH, LOW, HIGH
    );

    run_case(
        "same value",
        HIGH, LOW, HIGH, LOW,
        HIGH, LOW, HIGH, LOW
    );

    run_case(
        "conflict all bits",
        HIGH, LOW, HIGH, LOW,
        LOW, HIGH, LOW, HIGH
    );

    run_case(
        "partial conflict",
        HIGH, LOW, HIGH, LOW,
        HIGH, HIGH, FLOATING, LOW
    );

    return 0;
}