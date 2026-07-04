#include "utils.h"

const charp signal_to_string(signal_t sig) {
  switch (sig) {
    case LOW: return "LOW";
    case HIGH: return "HIGH";
    case FLOATING: return "FLOATING";
    case CONFLICT: return "CONFLICT";
    default: return "INVALID";
  }
}