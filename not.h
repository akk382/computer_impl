#include "gate.h"

struct not_t {
  wire_t* in;
  wire_t* out;
};

typedef struct not_t not_t;

void not_update(not_t*);