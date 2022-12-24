#pragma once

#include "../core/ffp_core.h"

struct ffp_buffered {
    struct ffp_core core;
};

void ffp_buffered_init(struct ffp_buffered *self);

bool ffp_core_is_ready_to_queue_byte_to_send(struct ffp_core *self);
bool ffp_core_queue_byte_to_send(struct ffp_core *self, uint8_t byte);

bool ffp_core_is_ready_to_rx_raw_byte(struct ffp_core *self);
bool ffp_core_rx_raw_byte(struct ffp_core *self, uint8_t byte);
