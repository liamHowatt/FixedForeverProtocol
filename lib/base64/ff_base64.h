#pragma once

#include <stdint.h>
#include <stdbool.h>

bool ff_base64_encoded_len_is_valid(uint16_t encoded_len);

uint16_t ff_base64_encoded_len(uint16_t decoded_len);

uint16_t ff_base64_decoded_len(uint16_t encoded_len);

void ff_base64_encode(uint8_t *dest, uint8_t *src, uint16_t src_len);

void ff_base64_decode(uint8_t *dest, uint8_t *src, uint16_t src_len);

