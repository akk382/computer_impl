#include "pmos.h"

struct pmos_net {
  pmos_t* p1;
  pmos_t* p2;
  wire_t* drain; // final result. Used for the output(most useful in parallel network).
};

typedef struct pmos_net pmos_net;

// In series, we consider p1 source is connected to VDD/HIGH.
//  Rest of the below are connected to the drain in series.
void pmos_series_update(pmos_net*);
void pmos_parallel_update(pmos_net*);