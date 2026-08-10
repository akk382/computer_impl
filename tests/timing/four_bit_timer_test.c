#include <stdio.h>

#include "../../include/timing/clock.h"
#include "../../include/timing/four_bit_timer.h"
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

static void print_timer_state(const char *label, const four_bit_timer_t *timer)
{
    printf("%-28s ", label);

    printf("CLK=%s ", signal_to_string(timer->CLK->val));
    printf("EN=%s ", signal_to_string(timer->EN->val));
    printf("RST=%s ", signal_to_string(timer->RST->val));
    printf("LIMIT_LOAD=%s | ", signal_to_string(timer->LIMIT_LOAD->val));

    print_nibble("COUNT", &timer->OUT);
    printf(" | ");

    print_nibble("LIMIT", &timer->LIMIT_Q);
    printf(" | ");

    printf("IRQ=%s\n", signal_to_string(timer->IRQ->val));
}

/*
 * One full simulated clock cycle.
 *
 * LOW phase:
 *   master latches observe inputs
 *
 * HIGH phase:
 *   rising edge commits state
 *
 * LOW phase:
 *   prepare for next cycle
 */
static void timer_cycle(clock_t *clk, four_bit_timer_t *timer)
{
    clock_low(clk);
    four_bit_timer_update(timer);

    clock_high(clk);
    four_bit_timer_update(timer);

    clock_low(clk);
    four_bit_timer_update(timer);
}

int main(void)
{
    wire_t clk_wire = { LOW };
    wire_t en = { LOW };
    wire_t rst = { LOW };
    wire_t limit_load = { LOW };
    wire_t irq = { LOW };

    clock_t clk = {
        .out = &clk_wire
    };

    /*
     * Current counter visible output Q.
     * Start dirty/nonzero so reset proves something.
     */
    wire_t q0 = { HIGH };
    wire_t q1 = { LOW };
    wire_t q2 = { HIGH };
    wire_t q3 = { LOW };

    /*
     * Limit input D.
     * We will first load limit = 0011.
     */
    wire_t ld0 = { HIGH };
    wire_t ld1 = { HIGH };
    wire_t ld2 = { LOW };
    wire_t ld3 = { LOW };

    /*
     * Limit register persistent state.
     */
    wire_t lq0 = { LOW };
    wire_t lq1 = { LOW };
    wire_t lq2 = { LOW };
    wire_t lq3 = { LOW };

    wire_t lqb0 = { LOW };
    wire_t lqb1 = { LOW };
    wire_t lqb2 = { LOW };
    wire_t lqb3 = { LOW };

    wire_t lqm0 = { LOW };
    wire_t lqm1 = { LOW };
    wire_t lqm2 = { LOW };
    wire_t lqm3 = { LOW };

    wire_t lqmb0 = { LOW };
    wire_t lqmb1 = { LOW };
    wire_t lqmb2 = { LOW };
    wire_t lqmb3 = { LOW };

    four_bit_timer_t timer = {
        .CLK = &clk_wire,
        .EN = &en,
        .RST = &rst,

        .OUT = { &q0, &q1, &q2, &q3 },

        .LIMIT_D = { &ld0, &ld1, &ld2, &ld3 },
        .LIMIT_LOAD = &limit_load,

        .LIMIT_Q = { &lq0, &lq1, &lq2, &lq3 },
        .LIMIT_Qb = { &lqb0, &lqb1, &lqb2, &lqb3 },
        .LIMIT_Qm = { &lqm0, &lqm1, &lqm2, &lqm3 },
        .LIMIT_Qmb = { &lqmb0, &lqmb1, &lqmb2, &lqmb3 },

        .IRQ = &irq
    };

    print_timer_state("initial", &timer);

    /*
     * Test 1:
     * Load LIMIT = 0011 and reset counter to 0000.
     *
     * LIMIT_LOAD HIGH -> limit register captures LIMIT_D.
     * RST HIGH        -> counter resets to 0000.
     * EN LOW          -> counter does not count.
     */
    limit_load.val = HIGH;
    rst.val = HIGH;
    en.val = LOW;

    timer_cycle(&clk, &timer);
    print_timer_state("load limit 0011/reset", &timer);

    /*
     * Stop loading limit.
     * Release reset.
     */
    limit_load.val = LOW;
    rst.val = LOW;
    en.val = LOW;

    timer_cycle(&clk, &timer);
    print_timer_state("hold at 0000", &timer);

    /*
     * Test 2:
     * Enable counting.
     * LIMIT = 0011.
     *
     * IRQ should become HIGH when COUNT reaches 0011.
     */
    en.val = HIGH;

    timer_cycle(&clk, &timer);
    print_timer_state("count 1", &timer);

    timer_cycle(&clk, &timer);
    print_timer_state("count 2", &timer);

    timer_cycle(&clk, &timer);
    print_timer_state("count 3 irq high", &timer);

    timer_cycle(&clk, &timer);
    print_timer_state("count 4 irq low", &timer);

    /*
     * Test 3:
     * Pause counter.
     * COUNT should hold at 0100.
     */
    en.val = LOW;

    timer_cycle(&clk, &timer);
    print_timer_state("pause 1", &timer);

    timer_cycle(&clk, &timer);
    print_timer_state("pause 2", &timer);

    /*
     * Test 4:
     * Resume counter.
     * It should continue from 0100 to 0101.
     */
    en.val = HIGH;

    timer_cycle(&clk, &timer);
    print_timer_state("resume count 5", &timer);

    /*
     * Test 5:
     * Load a new limit = 0101 while count is already 0101.
     * IRQ should become HIGH after the limit register captures 0101.
     */
    ld3.val = LOW;
    ld2.val = HIGH;
    ld1.val = LOW;
    ld0.val = HIGH;

    limit_load.val = HIGH;
    en.val = LOW;
    rst.val = LOW;

    timer_cycle(&clk, &timer);
    print_timer_state("load limit 0101", &timer);

    /*
     * Test 6:
     * Reset counter again while limit remains 0101.
     * IRQ should go LOW because COUNT = 0000 and LIMIT = 0101.
     */
    limit_load.val = LOW;
    rst.val = HIGH;
    en.val = LOW;

    timer_cycle(&clk, &timer);
    print_timer_state("reset count only", &timer);

    return 0;
}