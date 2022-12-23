#pragma once

#include <stdint.h>

struct ffp_CircularBuffer {
    uint8_t *mem_ptr;
    uint16_t mem_size;
    uint16_t len;
    uint16_t first_out;
};

void ffp_CircularBuffer_init(struct ffp_CircularBuffer *self, uint8_t *mem_ptr, uint16_t mem_size);

void ffp_CircularBuffer_enqueue(struct ffp_CircularBuffer *self, uint8_t x);

uint8_t ffp_CircularBuffer_dequeue(struct ffp_CircularBuffer *self);

