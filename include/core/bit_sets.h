#ifndef BIT_SETS_H
#define BIT_SETS_H

#include "wire.h"

struct two_bit {
  wire_t* bit0;
  wire_t* bit1;
};

struct three_bit {
  wire_t* bit0;
  wire_t* bit1;
  wire_t* bit2;
};

struct nibble {
  wire_t* bit0;
  wire_t* bit1;
  wire_t* bit2;
  wire_t* bit3;
};

typedef struct two_bit two_bit;
typedef struct three_bit three_bit;
typedef struct nibble nibble;

#endif