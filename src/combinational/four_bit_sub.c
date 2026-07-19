/*
Use two’s-complement subtraction:

A - B = A + NOT(B) + 1

for four bits: 4 NOT gates + 1 four bit adder + 1 four bit incrementer
*/

#include "../../include/combinational/four_bit_sub.h"
#include "../../include/core/bit_sets.h"
#include "../../include/combinational/four_bit_not.h"
#include "../../include/combinational/four_bit_adder.h"
#include "../../include/combinational/four_bit_inc.h"
#include "../../include/core/wire.h"

void fbs_update(four_bit_sub* fbs) {
  four_bit_not fbn;
  four_bit_adder fba;
  four_bit_inc fbi;

  wire_t fbn_b0, fbn_b1, fbn_b2, fbn_b3;
  wire_t fba_b0, fba_b1, fba_b2, fba_b3;
  nibble fbn_out = {&fbn_b0, &fbn_b1, &fbn_b2, &fbn_b3};
  nibble fba_sum = {&fba_b0, &fba_b1, &fba_b2, &fba_b3};
  wire_t fba_carry, fbi_carry;


  fba.in1 = fbs->in1;

  fbn.in = fbs->in2;
  fbn.out = fbn_out;

  fba.in2 = fbn.out;
  fba.carry = &fba_carry;
  fba.sum = fba_sum;

  fbi.in = fba.sum;
  fbi.out = fbs->out;
  fbi.carry = &fbi_carry;

  fbn_update(&fbn);
  fba_update(&fba);
  fbi_update(&fbi);
}