#include "wire.h"

struct bin_gate {
  wire_t* in1;
  wire_t* in2;
  wire_t* out;
};

typedef struct bin_gate bin_gate_t;