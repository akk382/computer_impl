#include "../../include/combinational/four_to_two_encoder.h"
#include "../../include/gates/or.h"

void ftte_update(four_to_two_encoder* ftte) {
  or_t or0, or1;

  or0.in1 = ftte->in1;
  or0.in2 = ftte->in3;
  or0.out = ftte->out0;

  or1.in1 = ftte->in2;
  or1.in2 = ftte->in3;
  or1.out = ftte->out1;

  or_update(&or0);
  or_update(&or1);
}