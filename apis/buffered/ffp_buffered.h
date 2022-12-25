#pragma once

#include "../core/ffp_core.h"
#include "../../lib/CircularBuffer/ffp_CircularBuffer.h"

struct ffp_buffered_interface {
    void (*receive_message)(uint8_t *, uint8_t);
    void (*tx_raw_data)(uint8_t *, uint16_t);
};

struct ffp_buffered {
    struct ffp_buffered_interface *interface;
    struct ffp_core core;
    struct ffp_CircularBuffer tx_buffer;
    uint8_t raw_tx_buffer[370];
    uint16_t raw_tx_buffer_i;
    uint8_t actually_received_message_buffer[255];
    uint8_t actually_received_message_buffer_i;
};

void ffp_buffered_init(
    struct ffp_buffered *self,
    struct ffp_buffered_interface *interface,
    uint8_t *tx_buffer_mem,
    uint16_t tx_buffer_mem_len
);

void ffp_buffered_queue_message_to_send(struct ffp_buffered *self, uint8_t address, uint8_t *message, uint8_t length);

void ffp_buffered_rx_raw_data(struct ffp_buffered *self, uint8_t *message, uint16_t length);

bool ffp_buffered_can_queue_message(struct ffp_buffered *self, uint8_t length);
