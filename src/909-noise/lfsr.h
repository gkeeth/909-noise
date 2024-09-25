#ifndef LFSR_H
#define LFSR_H

#include <stdint.h>

/*
 * Advance the LFSR, shifting in the XOR'd input bit.
 *
 * The LFSR is a 31-bit maximal-length LFSR with taps at bits 13 and 31 (1..32).
 *
 * Arguments:
 * - lfsr:
 *      register value. Used as input and output; updated value is written back
 *      to the same variable. Must be initialized to a nonzero value before
 *      usage.
 * - output:
 *      output bit shifted out from the register. The bit of interest is in
 *      output's LSB; all other bits are zero.
 */
void lfsr_step(uint32_t *lfsr, uint32_t *output);

#endif // LFSR_H
