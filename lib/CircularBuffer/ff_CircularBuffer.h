#pragma once

#include <stdint.h>

struct ff_CircularBuffer {
    uint8_t *mem_ptr;
    uint16_t mem_size;
    uint16_t len;
    uint16_t first_out;
};

void ff_CircularBuffer_init(struct ff_CircularBuffer *self, uint8_t *mem_ptr, uint16_t mem_size);

void ff_CircularBuffer_enqueue(struct ff_CircularBuffer *self, uint8_t x);

uint8_t ff_CircularBuffer_dequeue(struct ff_CircularBuffer *self);

