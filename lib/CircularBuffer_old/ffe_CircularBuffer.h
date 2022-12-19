#pragma once

#include <stdint.h>
#include <stddef.h>

struct ffe_CircularBuffer {
    uint8_t *mem_ptr;
    size_t mem_size;
    size_t len;
    size_t li;
    size_t fo;
};

void ffe_CircularBuffer_init(struct ffe_CircularBuffer *self, uint8_t *mem_ptr, size_t mem_size);

void ffe_CircularBuffer_enqueue(struct ffe_CircularBuffer *self, uint8_t x);

uint8_t ffe_CircularBuffer_dequeue(struct ffe_CircularBuffer *self);

