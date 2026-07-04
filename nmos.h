#include "wire.h"

struct nmos {
  wire_t* control;
  wire_t* output;
};

typedef struct nmos nmos_t;

void nmos_update(nmos_t*);