#include <stdio.h>

#include "four_bit_reg.h"
#include "utils.h"

static void print_nibble(const nibble *n)
{
    printf(
        "%s%s%s%s",
        signal_to_string(n->bit3->val),
        signal_to_string(n->bit2->val),
        signal_to_string(n->bit1->val),
        signal_to_string(n->bit0->val)
    );
}

static void print_state(
    const char *label,
    const four_bit_reg *reg
) {
    printf("%-28s D=", label);
    print_nibble(&reg->D);

    printf(
        " LOAD=%s CLK=%s Q=",
        signal_to_string(reg->LOAD->val),
        signal_to_string(reg->CLK->val)
    );

    print_nibble(&reg->Q);
    printf("\n");
}

int main(void)
{
    wire_t load = { LOW };
    wire_t clk  = { LOW };

    wire_t d0 = { LOW };
    wire_t d1 = { LOW };
    wire_t d2 = { LOW };
    wire_t d3 = { LOW };

    wire_t qm0 = { LOW };
    wire_t qm1 = { LOW };
    wire_t qm2 = { LOW };
    wire_t qm3 = { LOW };

    wire_t qmb0 = { HIGH };
    wire_t qmb1 = { HIGH };
    wire_t qmb2 = { HIGH };
    wire_t qmb3 = { HIGH };

    wire_t q0 = { LOW };
    wire_t q1 = { LOW };
    wire_t q2 = { LOW };
    wire_t q3 = { LOW };

    wire_t qb0 = { HIGH };
    wire_t qb1 = { HIGH };
    wire_t qb2 = { HIGH };
    wire_t qb3 = { HIGH };

    four_bit_reg reg = {
        .LOAD = &load,
        .CLK = &clk,

        .D = { &d0, &d1, &d2, &d3 },

        .Qm = { &qm0, &qm1, &qm2, &qm3 },
        .Qmb = { &qmb0, &qmb1, &qmb2, &qmb3 },

        .Q = { &q0, &q1, &q2, &q3 },
        .Qb = { &qb0, &qb1, &qb2, &qb3 }
    };

    /*
     * Test 1:
     * LOAD=LOW, D=1010.
     * Q must remain 0000 on the rising edge.
     */
    d3.val = HIGH;
    d2.val = LOW;
    d1.val = HIGH;
    d0.val = LOW;

    load.val = LOW;
    clk.val = LOW;
    fbr_update(&reg);
    print_state("Prepare 1010, LOAD LOW", &reg);

    clk.val = HIGH;
    fbr_update(&reg);
    print_state("Rising edge", &reg);

    /*
     * Return clock LOW before the next rising edge.
     */
    clk.val = LOW;
    fbr_update(&reg);

    /*
     * Test 2:
     * LOAD=HIGH, D=1010.
     * Q must become 1010.
     */
    load.val = HIGH;
    fbr_update(&reg);
    print_state("Prepare load 1010", &reg);

    clk.val = HIGH;
    fbr_update(&reg);
    print_state("Rising edge", &reg);

    /*
     * Test 3:
     * LOAD=LOW, D=0101.
     * Q must remain 1010.
     */
    clk.val = LOW;

    d3.val = LOW;
    d2.val = HIGH;
    d1.val = LOW;
    d0.val = HIGH;

    load.val = LOW;
    fbr_update(&reg);
    print_state("Prepare 0101, LOAD LOW", &reg);

    clk.val = HIGH;
    fbr_update(&reg);
    print_state("Rising edge", &reg);

    /*
     * Test 4:
     * LOAD=HIGH, D=0101.
     * Q must become 0101.
     */
    clk.val = LOW;
    load.val = HIGH;
    fbr_update(&reg);
    print_state("Prepare load 0101", &reg);

    clk.val = HIGH;
    fbr_update(&reg);
    print_state("Rising edge", &reg);

    return 0;
}