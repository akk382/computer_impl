/**
 * Build a D flip-flop, which changes Q only at a clock transition instead of during the entire HIGH level.
 * A common implementation uses two D latches:
D
│
▼
Master latch
│
▼
Slave latch
│
▼
Q

The two latches use opposite clock phases:

Master enable = NOT(CLOCK)
Slave enable  = CLOCK

When CLOCK = LOW, the master can follow D, while the slave holds.

When the clock changes to HIGH, the master closes and the slave opens, transferring the master’s stored value to Q.

That creates a rising-edge-triggered D flip-flop.

Task

Implement a rising-edge D flip-flop using:

exactly two existing D latches,
exactly one NOT gate,
persistent intermediate master-state wires.
 */

#include "d_flipflop.h"

#include "d_latch.h"
#include "not.h"

void dff_update(const d_flipflop* dfl) {
 not_t n;
 d_latch master, slave;

 wire_t n_out;

 n.in = dfl->CLK;
 n.out = &n_out;

 master.E = n.out;
 master.D = dfl->D;
 master.Q = dfl->Qm;
 master.Qb = dfl->Qmb;

 slave.E = dfl->CLK;
 slave.D = master.Q;
 slave.Q = dfl->Q;
 slave.Qb = dfl->Qb;

 not_update(&n);
 dl_update(&master);
 dl_update(&slave);
}
