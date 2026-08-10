#include "../../include/timing/clock.h"

/**
 * This is allowed to use direct .val because
 * the clock is an external simulator driver,
 * like a power supply or test input.
 * It is not hardware logic built from gates.
 */

void clock_low(const clock_t* clk)
{
  clk->out->val = LOW;
}

void clock_high(const clock_t* clk)
{
  clk->out->val = HIGH;
}

void clock_tick(const clock_t* clk)
{
  clock_low(clk);
  clock_high(clk);
}