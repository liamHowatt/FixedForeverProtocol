#pragma once

#include <stdint.h>
#include <stddef.h>

struct ff_CircularBuffer {
    uint8_t *mem_ptr;
    size_t mem_size;
    size_t len;
    size_t li;
    size_t fo;
};

void ff_CircularBuffer_init(struct ff_CircularBuffer *self, uint8_t *mem_ptr, size_t mem_size);

void ff_CircularBuffer_enqueue(struct ff_CircularBuffer *self, uint8_t x);

uint8_t ff_CircularBuffer_dequeue(struct ff_CircularBuffer *self);

