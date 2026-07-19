#include <stdio.h>

#include "../include/bus/two_register_bus.h"
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

static void print_state(const char *label, const two_register_bus_t *trb)
{
    printf("%-28s ", label);

    print_nibble("R0", &trb->r0_Q);
    printf(" R0_OE=%s | ", signal_to_string(trb->r0_OE->val));

    print_nibble("R1", &trb->r1_Q);
    printf(" R1_OE=%s | ", signal_to_string(trb->r1_OE->val));

    print_nibble("BUS", &trb->bus);
    printf("\n");
}

int main(void)
{
    /*
     * R0 = 1010
     */
    wire_t r0_b0 = { LOW };
    wire_t r0_b1 = { HIGH };
    wire_t r0_b2 = { LOW };
    wire_t r0_b3 = { HIGH };

    /*
     * R1 = 0101
     */
    wire_t r1_b0 = { HIGH };
    wire_t r1_b1 = { LOW };
    wire_t r1_b2 = { HIGH };
    wire_t r1_b3 = { LOW };

    wire_t r0_oe = { LOW };
    wire_t r1_oe = { LOW };

    wire_t bus0 = { FLOATING };
    wire_t bus1 = { FLOATING };
    wire_t bus2 = { FLOATING };
    wire_t bus3 = { FLOATING };

    two_register_bus_t trb = {
        .r0_Q = { &r0_b0, &r0_b1, &r0_b2, &r0_b3 },
        .r0_OE = &r0_oe,

        .r1_Q = { &r1_b0, &r1_b1, &r1_b2, &r1_b3 },
        .r1_OE = &r1_oe,

        .bus = { &bus0, &bus1, &bus2, &bus3 }
    };

    /*
     * Case 1:
     * R0 disconnected, R1 disconnected
     * BUS should be FLOATING FLOATING FLOATING FLOATING
     */
    r0_oe.val = LOW;
    r1_oe.val = LOW;
    trb_update(&trb);
    print_state("both disabled", &trb);

    /*
     * Case 2:
     * R0 drives bus, R1 disconnected
     * BUS should be 1010
     */
    r0_oe.val = HIGH;
    r1_oe.val = LOW;
    trb_update(&trb);
    print_state("R0 enabled", &trb);

    /*
     * Case 3:
     * R0 disconnected, R1 drives bus
     * BUS should be 0101
     */
    r0_oe.val = LOW;
    r1_oe.val = HIGH;
    trb_update(&trb);
    print_state("R1 enabled", &trb);

    /*
     * Case 4:
     * R0 and R1 both drive different values
     * R0 = 1010, R1 = 0101
     * BUS should be CONFLICT CONFLICT CONFLICT CONFLICT
     */
    r0_oe.val = HIGH;
    r1_oe.val = HIGH;
    trb_update(&trb);
    print_state("both enabled conflict", &trb);

    /*
     * Case 5:
     * Change R1 to same value as R0: 1010
     * Both enabled should now be valid, not conflict.
     */
    r1_b3.val = HIGH;
    r1_b2.val = LOW;
    r1_b1.val = HIGH;
    r1_b0.val = LOW;

    r0_oe.val = HIGH;
    r1_oe.val = HIGH;
    trb_update(&trb);
    print_state("both same value", &trb);

    return 0;
}