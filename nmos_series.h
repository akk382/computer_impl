#include "nmos.h"

struct nmos_ser {
  nmos_t* n1;
  nmos_t* n2;
};

typedef struct nmos_ser nmos_ser;

void nmos_net_update(nmos_ser*);