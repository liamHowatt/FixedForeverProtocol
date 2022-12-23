#include "ffp_CircularBuffer.h"

void ffp_CircularBuffer_init(struct ffp_CircularBuffer *self, uint8_t *mem_ptr, uint16_t mem_size) {
    self->mem_ptr = mem_ptr;
    self->mem_size = mem_size;
    self->len = 0;
    self->first_out = 0;
}

void ffp_CircularBuffer_enqueue(struct ffp_CircularBuffer *self, uint8_t x) {
    uint16_t last_in = (self->first_out + self->len) % self->mem_size;
    self->mem_ptr[last_in] = x;
    if (self->len != self->mem_size) {
        self->len += 1;
    } else {
        self->first_out = (self->first_out + 1) % self->mem_size;
    }
}

uint8_t ffp_CircularBuffer_dequeue(struct ffp_CircularBuffer *self) {
    if (self->len == 0) {
        return 0;
    }
    uint8_t ret = self->mem_ptr[self->first_out];
    self->first_out = (self->first_out + 1) % self->mem_size;
    self->len -= 1;
    return ret;
}

