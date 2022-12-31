#include "ffp_core.h"

#include <string.h>

void ffp_core_init(
    struct ffp_core *self,
    uint8_t address,
    void (*user_in_cb)(void *userobj, uint8_t address, uint8_t *message, uint8_t len),
    void (*bus_out_cb)(void *userobj, uint8_t *data, uint16_t len),
    void (*sleep_cb)(void *userobj, uint16_t duration, uint16_t sleep_id),
    uint8_t *user_out_buff_mem,
    uint16_t user_out_buff_mem_len
) {
    self->address = address;
    self->user_in_cb = user_in_cb;
    self->bus_out_cb = bus_out_cb;
    self->sleep_cb = sleep_cb;
    ffp_CircularBuffer_init(
        &self->user_out_circular_buffer,
        user_out_buff_mem,
        user_out_buff_mem_len
    );
    self->trying_to_send = false;
}

uint16_t ffp_core_user_out_circular_buffer_space_left(struct ffp_core *self) {
    uint16_t circular_buffer_space_left = self->user_out_circular_buffer.mem_size - self->user_out_circular_buffer.len;
    if (circular_buffer_space_left <= 2) {
        return 0;
    }
    return circular_buffer_space_left - 2;
}

void ffp_core_user_out(struct ffp_core *self, void *userobj, uint8_t address, uint8_t *message, uint8_t len) {
    if (!(self->trying_to_send)) {
        self->trying_to_send = true;
        memcpy(self->send_buffer, message, len);
    }
    else {
        if (len > ffp_core_user_out_circular_buffer_space_left(self)) {
            return;
        }
        ffp_CircularBuffer_enqueue(&self->user_out_circular_buffer, address);
        ffp_CircularBuffer_enqueue(&self->user_out_circular_buffer, len);
        for (uint8_t i=0; i<len; i++) {
            ffp_CircularBuffer_enqueue(&self->user_out_circular_buffer, message[i]);
        }
    }
}
bool ffp_core_user_out_ready(struct ffp_core *self, uint16_t message_len) {
    if (!(self->trying_to_send)) {
        return true;
    }
    uint16_t circular_buffer_space_left = self->user_out_circular_buffer.mem_size - self->user_out_circular_buffer.len;
    if (circular_buffer_space_left <= 2) {
        return false;
    }
    return message_len <= ffp_core_user_out_circular_buffer_space_left(self);
}

void ffp_core_bus_in(struct ffp_core *self, void *userobj, uint8_t *data, uint16_t len) {

}

void ffp_core_sleep_expired(struct ffp_core *self, void *userobj, uint16_t sleep_id) {

}
