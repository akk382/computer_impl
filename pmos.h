#include "wire.h"

struct pmos_old {
  wire_t* control;
  wire_t* output;
};

struct pmos {
  wire_t* gate; // which we control
  wire_t* source; // if used by single nmos, default should connect to LOW/GND. Else it should be either LOW/FLOATING.
  wire_t* drain; // output
};

typedef struct pmos_old pmos_old_t;
typedef struct pmos pmos_t;

void pmos_update(pmos_t*);