#pragma once

#include "../core/ffp_core.h"
#include "../../lib/CircularBuffer/ffp_CircularBuffer.h"

struct ffp_buffered {
    struct ffp_core core;
};

void ffp_buffered_init(
    struct ffp_buffered *self
);

// user out  -->  bus out
// bus in    -->  user in

bool ffp_buffered_user_out(struct ffp_buffered *self,
    uint8_t address, uint8_t *message, uint8_t length,
    
);

void ffp_buffered_bus_in_ready(struct ffp_buffered *self, uint8_t *message, uint16_t length);
void ffp_buffered_bus_in(struct ffp_buffered *self, uint8_t *message, uint16_t length);

bool ffp_buffered_can_queue_message(struct ffp_buffered *self, uint8_t length);
