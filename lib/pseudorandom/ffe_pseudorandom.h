#pragma once

#include <stdint.h>

uint8_t ffe_pseudorandom_lfsr_bit(uint32_t *state);

uint16_t ffe_pseudorandom_randint(uint32_t *state, uint16_t lower_bound, uint16_t upper_bound);
