#ifndef TWO_TO_FOUR_DECODER_H
#define TWO_TO_FOUR_DECODER_H

#include "wire.h"

struct two_to_four_decoder {
  wire_t* in0;
  wire_t* in1;

  wire_t* out0;
  wire_t* out1;
  wire_t* out2;
  wire_t* out3;
};

typedef struct two_to_four_decoder two_to_four_decoder;

void tt4_decoder_update(two_to_four_decoder*);

#endif