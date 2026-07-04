#include "wire.h"

struct pmos {
  wire_t* control;
  wire_t* output;
};

typedef struct pmos pmos_t;

void pmos_update(pmos_t*);