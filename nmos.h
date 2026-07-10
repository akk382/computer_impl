#ifndef NMOS_H
#define NMOS_H

#include "wire.h"

struct nmos_old {
  wire_t* control;
  wire_t* output;
};

struct nmos {
  wire_t* gate; // which we control
  wire_t* source; // if used by single nmos, default should connect to LOW/GND. Else it should be either LOW/FLOATING.
  wire_t* drain; // output
};

typedef struct nmos_old nmos_old_t;
typedef struct nmos nmos_t;

void nmos_update_old(nmos_old_t*);
void nmos_update(nmos_t*);

#endif