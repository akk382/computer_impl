#include <stdio.h>

#include "../../include/timing/four_bit_counter.h"
#include "../../include/timing/clock.h"
#include "../../include/core/utils.h"

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

static void print_counter_state(const char *label, const four_bit_counter_t *counter)
{
    printf("%-28s ", label);
    printf("CLK=%s ", signal_to_string(counter->CLK->val));
    printf("EN=%s ", signal_to_string(counter->EN->val));
    printf("RST=%s | ", signal_to_string(counter->RST->val));
    print_nibble("OUT", &counter->out);
    printf("\n");
}

/*
 * One full simulated clock cycle:
 *
 * CLK LOW  -> update circuit
 * CLK HIGH -> update circuit, rising edge commits register state
 * CLK LOW  -> update circuit, prepares master latch for next cycle
 */
static void counter_cycle(clock_t *clk, four_bit_counter_t *counter)
{
    clock_low(clk);
    four_bit_counter_update(counter);

    clock_high(clk);
    four_bit_counter_update(counter);

    clock_low(clk);
    four_bit_counter_update(counter);
}

int main(void)
{
    wire_t clk_wire = { LOW };
    wire_t en = { LOW };
    wire_t rst = { LOW };

    /*
     * Visible counter output.
     * Start intentionally nonzero so reset test proves something.
     */
    wire_t out0 = { HIGH };
    wire_t out1 = { LOW };
    wire_t out2 = { HIGH };
    wire_t out3 = { LOW };

    clock_t clk = {
        .out = &clk_wire
    };

    /*
     * Important:
     * This initializer zero-initializes qb/qm/qmb internal wires.
     * Since LOW = 0, they begin as LOW.
     */
    four_bit_counter_t counter = {
        .CLK = &clk_wire,
        .EN = &en,
        .RST = &rst,
        .out = { &out0, &out1, &out2, &out3 }
    };

    print_counter_state("initial", &counter);

    /*
     * Test 1:
     * RESET HIGH should clear counter to 0000 on rising edge.
     */
    rst.val = HIGH;
    en.val = LOW;

    counter_cycle(&clk, &counter);
    print_counter_state("after reset", &counter);

    /*
     * Test 2:
     * RESET LOW, EN HIGH.
     * Counter should increment every cycle.
     */
    rst.val = LOW;
    en.val = HIGH;

    counter_cycle(&clk, &counter);
    print_counter_state("count 1", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 2", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 3", &counter);

    /*
     * Test 3:
     * EN LOW should hold current value.
     */
    en.val = LOW;

    counter_cycle(&clk, &counter);
    print_counter_state("hold 1", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("hold 2", &counter);

    /*
     * Test 4:
     * EN HIGH resumes from previous value.
     */
    en.val = HIGH;

    counter_cycle(&clk, &counter);
    print_counter_state("resume: count 4", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 5", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 6", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 7", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 8", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 9", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 10", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 11", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 12", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 13", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 14", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("count 15", &counter);

    counter_cycle(&clk, &counter);
    print_counter_state("wrap to 0000", &counter);

    return 0;
}