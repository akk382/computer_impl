#ifndef CMOS_H
#define CMOS_H

#include "pmos.h"
#include "nmos.h"
#include "wire.h"

struct cmos {
  wire_t* control;
  wire_t* output;
};

typedef struct cmos cmos_t;

void cmos_update_old(cmos_t*);
void cmos_update(cmos_t*);

#endif