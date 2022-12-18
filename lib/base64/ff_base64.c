#include "ff_base64.h"

uint16_t ff_base64_encoded_len(uint16_t decoded_len) {
    uint16_t whole_sections = decoded_len / 3;
    uint16_t last_bytes = decoded_len % 3;

    uint16_t last_bytes_encoded;
    if (last_bytes == 0) {
        last_bytes_encoded = 0;
    }
    else {
        last_bytes_encoded = last_bytes + 1;
    }

    return (whole_sections * 4) + last_bytes_encoded;
}

bool ff_base64_encoded_len_is_valid(uint16_t encoded_len) {
    return encoded_len % 4 != 1;
}

uint16_t ff_base64_decoded_len(uint16_t encoded_len) {
    uint16_t whole_sections = encoded_len / 4;
    uint16_t last_bytes = encoded_len % 4;

    uint16_t last_bytes_decoded;
    if (last_bytes == 0) {
        last_bytes_decoded = 0;
    }
    else {
        last_bytes_decoded = last_bytes - 1;
    }

    return (whole_sections * 3) + last_bytes_decoded;
}

void ff_base64_encode(uint8_t *dest, uint8_t *src, uint16_t src_len) {
    while (src_len) {
        uint32_t frame = 0;
        uint8_t bytes_in_frame = 0;
        uint8_t byte_n_from_the_right = 2;
        while(src_len && bytes_in_frame < 3) {
            frame += ((uint32_t) (*(src++))) << (byte_n_from_the_right-- * 8);
            bytes_in_frame += 1;
            src_len -= 1;
        }
        bytes_in_frame += 1;
        byte_n_from_the_right = 3;
        while(bytes_in_frame) {
            bytes_in_frame -= 1;
            uint8_t six_bit = (frame >> (byte_n_from_the_right-- * 6)) & 0b111111;
            *(dest++) = six_bit + 34;
        }
    }
}

void ff_base64_decode(uint8_t *dest, uint8_t *src, uint16_t src_len) {
    while (src_len) {
        uint32_t frame = 0;
        uint8_t bytes_in_frame = 0;
        uint8_t byte_n_from_the_right = 3;
        while(src_len && bytes_in_frame < 4) {
            frame += ((uint32_t) ((*(src++)) - 34)) << (byte_n_from_the_right-- * 6);
            bytes_in_frame += 1;
            src_len -= 1;
        }
        bytes_in_frame -= 1;
        byte_n_from_the_right = 2;
        while(bytes_in_frame) {
            bytes_in_frame -= 1;
            *(dest++) = frame >> (byte_n_from_the_right-- * 8);
        }
    }
}
