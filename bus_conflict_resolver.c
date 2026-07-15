#include "bus_conflict_resolver.h"

void bcr_update(const bus_conflict_resolver_t* bcr) {
  if (bcr->driver0->val == HIGH) {
    if (bcr->driver1->val == FLOATING) {
      bcr->bus->val = HIGH;
    } else if (bcr->driver1->val == HIGH) {
      bcr->bus->val = HIGH;
    } else {
      bcr->bus->val = CONFLICT;
    }
  } else if (bcr->driver0->val == LOW) {
    if (bcr->driver1->val == FLOATING) {
      bcr->bus->val = LOW;
    } else if (bcr->driver1->val == LOW) {
      bcr->bus->val = LOW;
    } else {
      bcr->bus->val = CONFLICT;
    }
  } else {
    if (bcr->driver1->val == HIGH) {
      bcr->bus->val = HIGH;
    } else if (bcr->driver1->val == LOW) {
      bcr->bus->val = LOW;
    } else {
      bcr->bus->val = FLOATING;
    }
  }
}
