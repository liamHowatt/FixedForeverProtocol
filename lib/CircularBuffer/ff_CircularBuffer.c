#include "ff_CircularBuffer.h"

void ff_CircularBuffer_init(struct ff_CircularBuffer *self, uint8_t *mem_ptr, uint16_t mem_size) {
    self->mem_ptr = mem_ptr;
    self->mem_size = mem_size;
    self->len = 0;
    self->first_out = 0;
}

void ff_CircularBuffer_enqueue(struct ff_CircularBuffer *self, uint8_t x) {
    if (self->len == self->mem_size) {
        return;
    }
    uint16_t last_in = (self->first_out + self->len) % self->mem_size;
    self->mem_ptr[last_in] = x;
    self->len += 1;
}

uint8_t ff_CircularBuffer_dequeue(struct ff_CircularBuffer *self) {
    if (self->len == 0) {
        return 0;
    }
    uint8_t ret = self->mem_ptr[self->first_out];
    self->first_out = (self->first_out + 1) % self->mem_size;
    self->len -= 1;
    return ret;
}

