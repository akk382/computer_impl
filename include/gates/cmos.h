#ifndef CMOS_H
#define CMOS_H

#include "../core/wire.h"

struct cmos {
  wire_t* control;
  wire_t* output;
};

typedef struct cmos cmos_t;

void cmos_update_old(cmos_t*);
void cmos_update(cmos_t*);

#endif