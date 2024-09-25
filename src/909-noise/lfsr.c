#include "lfsr.h"

void lfsr_step(uint32_t *lfsr, uint32_t *output) {
    // taps are 31 (output) and 13 (1..32)
    uint32_t tap1 = (*lfsr >> 30) & 0x1;
    uint32_t tap2 = (*lfsr >> 12) & 0x1;
    uint32_t xor = tap1 ^ tap2;
    *lfsr = (*lfsr << 1) | xor;
    *output = tap1;
}
