#pragma once

#include "../lib/CircularBuffer/ffp_CircularBuffer.h"

#include <stdbool.h>
#include <stdint.h>

struct ffp_core {
    uint8_t address;
    void (*user_in_cb)(void *userobj, uint8_t address, uint8_t *message, uint8_t len);
    void (*bus_out_cb)(void *userobj, uint8_t *data, uint16_t len);
    void (*sleep_cb)(void *userobj, uint16_t duration, uint16_t sleep_id);
    struct ffp_CircularBuffer user_out_circular_buffer;
    bool trying_to_send;
    uint8_t send_buffer[255];
};

void ffp_core_init(
    struct ffp_core *self,
    uint8_t address,
    void (*user_in_cb)(void *userobj, uint8_t address, uint8_t *message, uint8_t len),
    void (*bus_out_cb)(void *userobj, uint8_t *data, uint16_t len),
    void (*sleep_cb)(void *userobj, uint16_t duration, uint16_t sleep_id),
    uint8_t *user_out_buff_mem,
    uint16_t user_out_buff_mem_len
);

void ffp_core_user_out(struct ffp_core *self, void *userobj, uint8_t address, uint8_t *message, uint8_t len);
bool ffp_core_user_out_ready(struct ffp_core *self, uint16_t message_len);

void ffp_core_bus_in(struct ffp_core *self, void *userobj, uint8_t *data, uint16_t len);

void ffp_core_sleep_expired(struct ffp_core *self, void *userobj, uint16_t sleep_id);
