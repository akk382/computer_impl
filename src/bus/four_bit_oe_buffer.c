#include "../../include/bus/four_bit_oe_buffer.h"
#include "../../include/bus/one_bit_oe_buffer.h"

void fboeb_update(const four_bit_oe_buffer_t* fboeb) {
  one_bit_oe_buffer_t obeb0, obeb1, obeb2, obeb3;

  obeb0.Q = fboeb->Q.bit0;
  obeb0.OE = fboeb->OE;
  obeb0.bus = fboeb->bus.bit0;

  obeb1.Q = fboeb->Q.bit1;
  obeb1.OE = fboeb->OE;
  obeb1.bus = fboeb->bus.bit1;

  obeb2.Q = fboeb->Q.bit2;
  obeb2.OE = fboeb->OE;
  obeb2.bus = fboeb->bus.bit2;

  obeb3.Q = fboeb->Q.bit3;
  obeb3.OE = fboeb->OE;
  obeb3.bus = fboeb->bus.bit3;

  oboe_update(&obeb0);
  oboe_update(&obeb1);
  oboe_update(&obeb2);
  oboe_update(&obeb3);
}
