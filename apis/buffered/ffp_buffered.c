#include "ffp_buffered.h"

bool ffp_buffered_is_ready_for_raw_tx_byte_cb(struct ffp_buffered *self) {
    return true;
}

bool ffp_buffered_raw_tx_byte_cb(struct ffp_buffered *self, uint8_t byte) {
    self->raw_tx_buffer[(self->raw_tx_buffer_i)++] = byte;
    if (byte == '\n') {
        self->interface->tx_raw_data(self->raw_tx_buffer, self->raw_tx_buffer_i);
        self->raw_tx_buffer_i = 0;
    }
    return true;
}

bool ffp_buffered_is_ready_to_actually_receive_byte_cb(struct ffp_buffered *self) {
    return true;
}

bool ffp_buffered_actually_receive_byte_cb(struct ffp_buffered *self, uint8_t byte) {
    if (byte == '\n') {
    }
    self->actually_received_message_buffer[(self->actually_received_message_buffer_i)++] = byte;
    return true;
}

struct ffp_core_interface ffp_buffered_adapter = {
    .is_ready_for_raw_tx_byte_cb = ffp_buffered_is_ready_for_raw_tx_byte_cb,
    .raw_tx_byte_cb = ffp_buffered_raw_tx_byte_cb,
    .is_ready_to_actually_receive_byte_cb = ffp_buffered_is_ready_to_actually_receive_byte_cb,
    .actually_receive_byte_cb = ffp_buffered_actually_receive_byte_cb,
};

void ffp_buffered_init(
    struct ffp_buffered *self,
    struct ffp_buffered_interface *interface,
    uint8_t *tx_buffer_mem,
    uint16_t tx_buffer_mem_len
) {
    self->interface = interface;
    ffp_core_init(&self->core, &ffp_buffered_adapter);
    ffp_CircularBuffer_init(&self->tx_buffer, tx_buffer_mem, tx_buffer_mem_len);
    self->raw_tx_buffer_i = 0;
    self->actually_received_message_buffer_i = 0;
}

void ffp_buffered_queue_message_to_send(struct ffp_buffered *self, uint8_t address, uint8_t *message, uint8_t length) {
    if (ffp_core_is_ready_to_queue_byte_to_send(&self->core)) {
        ffp_core_queue_byte_to_send(&self->core, address);
        ffp_core_queue_byte_to_send(&self->core, length);
        for (uint8_t i=0; i<length; i++) {
            ffp_core_queue_byte_to_send(&self->core, message[i]);
        }
    }
    else {
        ffp_CircularBuffer_enqueue(&self->tx_buffer, address);
        ffp_CircularBuffer_enqueue(&self->tx_buffer, length);
        for (uint8_t i=0; i<length; i++) {
            ffp_CircularBuffer_enqueue(&self->tx_buffer, message[i]);
        }
    }
}

void ffp_buffered_rx_raw_data(struct ffp_buffered *self, uint8_t *message, uint16_t length) {
    for (uint8_t i=0; i<length; i++) {
        ffp_core_rx_raw_byte(&self->core, message[i]);
    }
}

bool ffp_buffered_can_queue_message(struct ffp_buffered *self, uint8_t length) {
    if (ffp_core_is_ready_to_queue_byte_to_send(&self->core)) {
        return true;
    }
    uint16_t bytes_left = self->tx_buffer.mem_size - self->tx_buffer.len;
    if (bytes_left <= 2) {
        return false;
    }
    return length <= (bytes_left - 2);
}
