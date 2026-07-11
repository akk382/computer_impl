#ifndef FOUR_TO_TWO_ENCODER_H
#define FOUR_TO_TWO_ENCODER_H

#include "wire.h"

struct four_to_two_encoder {
  wire_t* in0;
  wire_t* in1;
  wire_t* in2;
  wire_t* in3;

  wire_t* out0;
  wire_t* out1;
};

typedef struct four_to_two_encoder four_to_two_encoder;

void ftte_update(four_to_two_encoder*);

#endif