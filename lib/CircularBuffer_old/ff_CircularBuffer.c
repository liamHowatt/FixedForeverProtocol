#include "ff_CircularBuffer.h"

void ff_CircularBuffer_init(struct ff_CircularBuffer *self, uint8_t *mem_ptr, size_t mem_size) {
    self->mem_ptr = mem_ptr;
    self->mem_size = mem_size;
    self->len = 0;
    self->li = 0;
    self->fo = 0;
}

void ff_CircularBuffer_enqueue(struct ff_CircularBuffer *self, uint8_t x) {
    if (self->len == self->mem_size) {
        return;
    }
    if (self->len != 0) {
        self->li = (self->li + 1) % self->mem_size;
    }
    self->mem_ptr[self->li] = x;
    self->len += 1;
}

uint8_t ff_CircularBuffer_dequeue(struct ff_CircularBuffer *self) {
    if (self->len == 0) {
        return 0;
    }
    uint8_t ret = self->mem_ptr[self->fo];
    if (self->len != 1) {
        self->fo = (self->fo + 1) % self->mem_size;
    }
    self->len -= 1;
    return ret;
}

