#ifndef NMOS_NET_H
#define NMOS_NET_H

#include "nmos.h"

struct nmos_net {
  nmos_t* n1;
  nmos_t* n2;
  wire_t* drain; // final result. Used for the output(most useful in parallel network).
};

typedef struct nmos_net nmos_net;

// In series, we consider n2 source is connected to GND/LOW.
//  Rest of the above are connected to the drain in series.
void nmos_series_update(nmos_net*);
void nmos_parallel_update(nmos_net*);

#endif