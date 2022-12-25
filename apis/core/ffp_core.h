#pragma once

#include <stdbool.h>
#include <stdint.h>

struct ffp_core_interface {
    bool (*is_ready_for_raw_tx_byte_cb)(void *);
    bool (*raw_tx_byte_cb)(void *, uint8_t);
    bool (*is_ready_to_actually_receive_byte_cb)(void *);
    bool (*actually_receive_byte_cb)(void *, int16_t);
};

struct ffp_core {
    struct ffp_core_interface *interface;
};

void ffp_core_init(
    struct ffp_core *self,
    struct ffp_core_interface *interface
);

bool ffp_core_is_ready_to_queue_byte_to_send(struct ffp_core *self);
bool ffp_core_queue_byte_to_send(struct ffp_core *self, uint8_t byte);

bool ffp_core_is_ready_to_rx_raw_byte(struct ffp_core *self);
bool ffp_core_rx_raw_byte(struct ffp_core *self, uint8_t byte);

