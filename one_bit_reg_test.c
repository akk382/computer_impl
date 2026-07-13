#include <stdio.h>

#include "one_bit_reg.h"
#include "utils.h"

static void print_state(
    const char *label,
    const wire_t *D,
    const wire_t *LOAD,
    const wire_t *CLK,
    const wire_t *Q,
    const wire_t *Qm
) {
    printf(
        "%-28s D=%s LOAD=%s CLK=%s -> Q=%s Qm=%s\n",
        label,
        signal_to_string(D->val),
        signal_to_string(LOAD->val),
        signal_to_string(CLK->val),
        signal_to_string(Q->val),
        signal_to_string(Qm->val)
    );
}

int main(void) {
    wire_t D     = { LOW };
    wire_t LOAD  = { LOW };
    wire_t CLK   = { LOW };

    wire_t Qm    = { LOW };
    wire_t Qmb   = { HIGH };
    wire_t Q     = { LOW };
    wire_t Qb    = { HIGH };

    one_bit_reg reg = {
        .LOAD = &LOAD,
        .CLK  = &CLK,
        .D    = &D,
        .Qm   = &Qm,
        .Qmb  = &Qmb,
        .Q    = &Q,
        .Qb   = &Qb
    };

    /*
     * Test 1:
     * LOAD is LOW, so changing D must not change the stored value.
     */
    CLK.val = LOW;
    LOAD.val = LOW;
    D.val = HIGH;
    obreg_update(&reg);
    print_state("LOAD=LOW, prepare HIGH", &D, &LOAD, &CLK, &Q, &Qm);

    CLK.val = HIGH;
    obreg_update(&reg);
    print_state("LOAD=LOW, rising edge", &D, &LOAD, &CLK, &Q, &Qm);

    /*
     * Return clock LOW before creating another rising edge.
     */
    CLK.val = LOW;
    obreg_update(&reg);
    print_state("Clock returns LOW", &D, &LOAD, &CLK, &Q, &Qm);

    /*
     * Test 2:
     * LOAD is HIGH, so HIGH should be stored on the next rising edge.
     */
    LOAD.val = HIGH;
    D.val = HIGH;
    obreg_update(&reg);
    print_state("LOAD=HIGH, prepare HIGH", &D, &LOAD, &CLK, &Q, &Qm);

    CLK.val = HIGH;
    obreg_update(&reg);
    print_state("LOAD=HIGH, rising edge", &D, &LOAD, &CLK, &Q, &Qm);

    /*
     * Test 3:
     * Disable loading, change D to LOW, and verify Q still holds HIGH.
     */
    CLK.val = LOW;
    LOAD.val = LOW;
    D.val = LOW;
    obreg_update(&reg);
    print_state("LOAD=LOW, D changes LOW", &D, &LOAD, &CLK, &Q, &Qm);

    CLK.val = HIGH;
    obreg_update(&reg);
    print_state("LOAD=LOW, rising edge", &D, &LOAD, &CLK, &Q, &Qm);

    /*
     * Test 4:
     * Enable loading and store LOW.
     */
    CLK.val = LOW;
    LOAD.val = HIGH;
    D.val = LOW;
    obreg_update(&reg);
    print_state("LOAD=HIGH, prepare LOW", &D, &LOAD, &CLK, &Q, &Qm);

    CLK.val = HIGH;
    obreg_update(&reg);
    print_state("LOAD=HIGH, rising edge", &D, &LOAD, &CLK, &Q, &Qm);

    return 0;
}
