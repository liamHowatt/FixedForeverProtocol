#pragma once

#include <stdbool.h>
#include <stdint.h>

struct ffp_core {
};

void ffp_core_init(
    struct ffp_core *self
);

bool ffp_core_user_out_ready(struct ffp_core *self);
bool ffp_core_user_out(struct ffp_core *self, int16_t byte);

bool ffp_core_bus_in_ready(struct ffp_core *self);
bool ffp_core_bus_in(struct ffp_core *self, uint8_t byte);

bool ffp_core_user_in_ready(struct ffp_core *self);
bool ffp_core_user_in(struct ffp_core *self, int16_t *byte);

bool ffp_core_bus_out_ready(struct ffp_core *self);
bool ffp_core_bus_out(struct ffp_core *self, uint8_t *byte);
