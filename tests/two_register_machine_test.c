#include <stdio.h>

#include "../include/machine/two_register_machine.h"
#include "../include/sequential/four_bit_reg.h"
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

static void print_state(const char *label, const two_register_machine_t *trm)
{
    printf("%-28s ", label);

    print_nibble("R0.Q", &trm->R0->Q);
    printf(" | ");

    print_nibble("R1.Q", &trm->R1->Q);
    printf(" | ");

    print_nibble("BUS", &trm->bus);
    printf("\n");
}

int main(void)
{
    wire_t clk = { LOW };

    wire_t r0_load = { LOW };
    wire_t r1_load = { LOW };

    wire_t r0_oe = { LOW };
    wire_t r1_oe = { LOW };

    /*
     * Persistent R0 state wires
     */
    wire_t r0_q0 = { LOW };
    wire_t r0_q1 = { HIGH };
    wire_t r0_q2 = { LOW };
    wire_t r0_q3 = { HIGH };

    wire_t r0_qb0 = { HIGH };
    wire_t r0_qb1 = { LOW };
    wire_t r0_qb2 = { HIGH };
    wire_t r0_qb3 = { LOW };

    wire_t r0_qm0 = { LOW };
    wire_t r0_qm1 = { HIGH };
    wire_t r0_qm2 = { LOW };
    wire_t r0_qm3 = { HIGH };

    wire_t r0_qmb0 = { HIGH };
    wire_t r0_qmb1 = { LOW };
    wire_t r0_qmb2 = { HIGH };
    wire_t r0_qmb3 = { LOW };

    /*
     * Persistent R1 state wires
     */
    wire_t r1_q0 = { HIGH };
    wire_t r1_q1 = { LOW };
    wire_t r1_q2 = { HIGH };
    wire_t r1_q3 = { LOW };

    wire_t r1_qb0 = { LOW };
    wire_t r1_qb1 = { HIGH };
    wire_t r1_qb2 = { LOW };
    wire_t r1_qb3 = { HIGH };

    wire_t r1_qm0 = { HIGH };
    wire_t r1_qm1 = { LOW };
    wire_t r1_qm2 = { HIGH };
    wire_t r1_qm3 = { LOW };

    wire_t r1_qmb0 = { LOW };
    wire_t r1_qmb1 = { HIGH };
    wire_t r1_qmb2 = { LOW };
    wire_t r1_qmb3 = { HIGH };

    /*
     * D inputs start floating; trm_update will connect them to BUS.
     */
    wire_t r0_d0 = { FLOATING };
    wire_t r0_d1 = { FLOATING };
    wire_t r0_d2 = { FLOATING };
    wire_t r0_d3 = { FLOATING };

    wire_t r1_d0 = { FLOATING };
    wire_t r1_d1 = { FLOATING };
    wire_t r1_d2 = { FLOATING };
    wire_t r1_d3 = { FLOATING };

    wire_t bus0 = { FLOATING };
    wire_t bus1 = { FLOATING };
    wire_t bus2 = { FLOATING };
    wire_t bus3 = { FLOATING };

    four_bit_reg R0 = {
        .D = { &r0_d0, &r0_d1, &r0_d2, &r0_d3 },
        .CLK = &clk,
        .LOAD = &r0_load,
        .Qm = { &r0_qm0, &r0_qm1, &r0_qm2, &r0_qm3 },
        .Qmb = { &r0_qmb0, &r0_qmb1, &r0_qmb2, &r0_qmb3 },
        .Q = { &r0_q0, &r0_q1, &r0_q2, &r0_q3 },
        .Qb = { &r0_qb0, &r0_qb1, &r0_qb2, &r0_qb3 }
    };

    four_bit_reg R1 = {
        .D = { &r1_d0, &r1_d1, &r1_d2, &r1_d3 },
        .CLK = &clk,
        .LOAD = &r1_load,
        .Qm = { &r1_qm0, &r1_qm1, &r1_qm2, &r1_qm3 },
        .Qmb = { &r1_qmb0, &r1_qmb1, &r1_qmb2, &r1_qmb3 },
        .Q = { &r1_q0, &r1_q1, &r1_q2, &r1_q3 },
        .Qb = { &r1_qb0, &r1_qb1, &r1_qb2, &r1_qb3 }
    };

    two_register_machine_t trm = {
        .R0 = &R0,
        .r0_OE = &r0_oe,

        .R1 = &R1,
        .r1_OE = &r1_oe,

        .bus = { &bus0, &bus1, &bus2, &bus3 }
    };

    print_state("initial", &trm);

    /*
     * Prepare transfer R0 -> R1.
     */
    r0_oe.val = HIGH;
    r1_oe.val = LOW;

    r0_load.val = LOW;
    r1_load.val = HIGH;

    /*
     * Clock LOW phase.
     * Master latch in R1 should see the BUS value.
     */
    clk.val = LOW;
    trm_update(&trm);
    print_state("clock low, prepared", &trm);

    /*
     * Rising edge / clock HIGH phase.
     * R1 should capture R0's value.
     */
    clk.val = HIGH;
    trm_update(&trm);
    print_state("after rising edge", &trm);

    return 0;
}