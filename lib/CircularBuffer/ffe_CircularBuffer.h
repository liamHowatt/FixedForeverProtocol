#pragma once

#include <stdint.h>

struct ffe_CircularBuffer {
    uint8_t *mem_ptr;
    uint16_t mem_size;
    uint16_t len;
    uint16_t first_out;
};

void ffe_CircularBuffer_init(struct ffe_CircularBuffer *self, uint8_t *mem_ptr, uint16_t mem_size);

void ffe_CircularBuffer_enqueue(struct ffe_CircularBuffer *self, uint8_t x);

uint8_t ffe_CircularBuffer_dequeue(struct ffe_CircularBuffer *self);

