#pragma once

#include <stdint.h>
#include <stdbool.h>

bool ffp_base64_encoded_len_is_valid(uint16_t encoded_len);

uint16_t ffp_base64_encoded_len(uint16_t decoded_len);

uint16_t ffp_base64_decoded_len(uint16_t encoded_len);

bool ffp_base64_encoded_message_has_valid_chars(uint8_t *src, uint16_t src_len);

void ffp_base64_encode(uint8_t *dest, uint8_t *src, uint16_t src_len);

void ffp_base64_decode(uint8_t *dest, uint8_t *src, uint16_t src_len);

