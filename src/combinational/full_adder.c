#include "../../include/combinational/full_adder.h"
#include "../../include/combinational/half_adder.h"
#include "../../include/core/wire.h"
#include "../../include/gates/or.h"

void fa_update(full_adder* fa) {
  half_adder ha1, ha2;
  or_t r;

  wire_t partial_sum, carry1, carry2;

  ha1.in1 = fa->in1;
  ha1.in2 = fa->in2;
  ha1.sum = &partial_sum;
  ha1.carry = &carry1;

  ha2.in1 = ha1.sum;
  ha2.in2 = fa->c_in;
  ha2.sum = fa->sum;
  ha2.carry = &carry2;

  r.in1 = ha1.carry;
  r.in2 = ha2.carry;
  r.out = fa->c_out;

  ha_update(&ha1);
  ha_update(&ha2);
  or_update(&r);
}


/* ChatGPT's diagrams

                     FIRST HALF ADDER

                 ┌────────────────────┐
A ──────────────►│                    │
                 │    HALF ADDER 1    ├────► partial_sum
B ──────────────►│                    ├────► carry_1
                 └────────────────────┘
                              │
                              │ partial_sum
                              ▼

                    SECOND HALF ADDER

                 ┌────────────────────┐
partial_sum ────►│                    │
                 │    HALF ADDER 2    ├────► SUM
Carry-in ───────►│                    ├────► carry_2
                 └────────────────────┘


carry_1 ───────────────┐
                       ▼
                    ┌──────┐
                    │  OR  ├────────► Carry-out
                    └──────┘
                       ▲
carry_2 ───────────────┘

*/