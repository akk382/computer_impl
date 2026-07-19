#include "../../include/combinational/four_bit_inc.h"
#include "../../include/core/bit_sets.h"
#include "../../include/combinational/four_bit_adder.h"

void fbi_update(four_bit_inc* fbi) {
  wire_t bit0 = {HIGH}, bit1 = {LOW}, bit2 = {LOW}, bit3 = {LOW};
  nibble in2 = {&bit0, &bit1, &bit2, &bit3};

  four_bit_adder fba;
  fba.in1 = fbi->in;
  fba.in2 = in2;
  fba.carry = fbi->carry;
  fba.sum = fbi->out;
  
  fba_update(&fba);
}