#include "ffe_pseudorandom.h"

// copied from https://github.com/taylorza/go-lfsr/blob/7ec2b93980f950da1e36c6682771e6fe14c144c2/lfsr.go
uint8_t ffe_pseudorandom_lfsr_bit(uint32_t *state) {
    uint32_t s = *state;
    uint8_t s8 = s & 0xff;
    uint8_t xorsum = (s8 >> 0) ^ (s8 >> 2) ^ (s8 >> 6) ^ (s8 >> 7);
    *state = (s >> 1) | (((uint32_t) xorsum) << 31);
    return xorsum & 1;
}

uint16_t ffe_pseudorandom_randint(uint32_t *state, uint16_t lower_bound, uint16_t upper_bound) {
    if (lower_bound == upper_bound) {
        return lower_bound;
    }
    uint16_t no_more_than = upper_bound - lower_bound;

    uint8_t bit_width = 0;
    for (uint16_t temp=no_more_than; temp; temp>>=1) {
        bit_width += 1;
    }

    while (1) {
        uint16_t randint = 0;
        for (uint8_t i=0; i<bit_width; i++) {
            uint16_t bit = ffe_pseudorandom_lfsr_bit(state);
            randint += bit << i;
        }
        if (randint <= no_more_than) {
            return randint + lower_bound;
        }
    }
}
