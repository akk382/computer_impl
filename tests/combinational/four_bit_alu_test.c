#include <stdio.h>

#include "combinational/four_bit_alu.h"
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

    signal_t a3, signal_t a2, signal_t a1, signal_t a0,
    signal_t b3, signal_t b2, signal_t b1, signal_t b0,

    signal_t sel1,
    signal_t sel0
)
{
    wire_t a_b0 = { a0 };
    wire_t a_b1 = { a1 };
    wire_t a_b2 = { a2 };
    wire_t a_b3 = { a3 };

    wire_t b_b0 = { b0 };
    wire_t b_b1 = { b1 };
    wire_t b_b2 = { b2 };
    wire_t b_b3 = { b3 };

    wire_t s0 = { sel0 };
    wire_t s1 = { sel1 };

    wire_t out0 = { FLOATING };
    wire_t out1 = { FLOATING };
    wire_t out2 = { FLOATING };
    wire_t out3 = { FLOATING };

    wire_t carry = { FLOATING };

    four_bit_alu_t alu = {
        .in0 = { &a_b0, &a_b1, &a_b2, &a_b3 },
        .in1 = { &b_b0, &b_b1, &b_b2, &b_b3 },

        .sel0 = &s0,
        .sel1 = &s1,

        .out = { &out0, &out1, &out2, &out3 },

        .carry = &carry
    };

    four_bit_alu_update(&alu);

    printf("%-24s ", label);

    print_nibble("A", &alu.in0);
    printf(" | ");

    print_nibble("B", &alu.in1);
    printf(" | ");

    printf(
        "SEL=%s%s | ",
        signal_to_string(s1.val),
        signal_to_string(s0.val)
    );

    printf(
        "CARRY=%s | ",
        signal_to_string(carry.val)
    );

    print_nibble("OUT", &alu.out);
    printf("\n");
}

int main(void)
{
    /*
     * Selector meaning:
     *
     * SEL1 SEL0
     *  LOW  LOW  -> ADD
     *  LOW  HIGH -> SUB
     *  HIGH LOW  -> AND
     *  HIGH HIGH -> OR
     */

    /*
     * ADD tests.
     *
     * 0011 + 0001 = 0100
     */
    run_case(
        "ADD 3 + 1",
        LOW, LOW, HIGH, HIGH,
        LOW, LOW, LOW, HIGH,
        LOW, LOW
    );

    /*
     * 0111 + 0001 = 1000
     */
    run_case(
        "ADD 7 + 1",
        LOW, HIGH, HIGH, HIGH,
        LOW, LOW, LOW, HIGH,
        LOW, LOW
    );

    /*
     * 1111 + 0001 = 0000 modulo 16.
     * Carry is ignored for now.
     */
    run_case(
        "ADD 15 + 1 wrap",
        HIGH, HIGH, HIGH, HIGH,
        LOW, LOW, LOW, HIGH,
        LOW, LOW
    );

    /*
     * SUB tests.
     *
     * 0011 - 0001 = 0010
     */
    run_case(
        "SUB 3 - 1",
        LOW, LOW, HIGH, HIGH,
        LOW, LOW, LOW, HIGH,
        LOW, HIGH
    );

    /*
     * 0100 - 0011 = 0001
     */
    run_case(
        "SUB 4 - 3",
        LOW, HIGH, LOW, LOW,
        LOW, LOW, HIGH, HIGH,
        LOW, HIGH
    );

    /*
     * 0000 - 0001 = 1111 modulo 16.
     */
    run_case(
        "SUB 0 - 1 wrap",
        LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, HIGH,
        LOW, HIGH
    );

    /*
     * AND tests.
     *
     * 1010 AND 1100 = 1000
     */
    run_case(
        "AND 1010 1100",
        HIGH, LOW, HIGH, LOW,
        HIGH, HIGH, LOW, LOW,
        HIGH, LOW
    );

    /*
     * 1111 AND 0101 = 0101
     */
    run_case(
        "AND 1111 0101",
        HIGH, HIGH, HIGH, HIGH,
        LOW, HIGH, LOW, HIGH,
        HIGH, LOW
    );

    /*
     * 0000 AND 1111 = 0000
     */
    run_case(
        "AND 0000 1111",
        LOW, LOW, LOW, LOW,
        HIGH, HIGH, HIGH, HIGH,
        HIGH, LOW
    );

    /*
     * OR tests.
     *
     * 1010 OR 1100 = 1110
     */
    run_case(
        "OR 1010 1100",
        HIGH, LOW, HIGH, LOW,
        HIGH, HIGH, LOW, LOW,
        HIGH, HIGH
    );

    /*
     * 0000 OR 0101 = 0101
     */
    run_case(
        "OR 0000 0101",
        LOW, LOW, LOW, LOW,
        LOW, HIGH, LOW, HIGH,
        HIGH, HIGH
    );

    /*
     * 1111 OR 0000 = 1111
     */
    run_case(
        "OR 1111 0000",
        HIGH, HIGH, HIGH, HIGH,
        LOW, LOW, LOW, LOW,
        HIGH, HIGH
    );

    /*
     * Same A/B, different selector.
     * This proves selector lines choose the operation.
     *
     * A = 0110
     * B = 0011
     *
     * ADD -> 1001
     * SUB -> 0011
     * AND -> 0010
     * OR  -> 0111
     */
    run_case(
        "same inputs ADD",
        LOW, HIGH, HIGH, LOW,
        LOW, LOW, HIGH, HIGH,
        LOW, LOW
    );

    run_case(
        "same inputs SUB",
        LOW, HIGH, HIGH, LOW,
        LOW, LOW, HIGH, HIGH,
        LOW, HIGH
    );

    run_case(
        "same inputs AND",
        LOW, HIGH, HIGH, LOW,
        LOW, LOW, HIGH, HIGH,
        HIGH, LOW
    );

    run_case(
        "same inputs OR",
        LOW, HIGH, HIGH, LOW,
        LOW, LOW, HIGH, HIGH,
        HIGH, HIGH
    );

    return 0;
}