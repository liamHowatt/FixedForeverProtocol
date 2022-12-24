#pragma once

#include <stdint.h>
#include <stdbool.h>

// 0..4       4
// <checksum>|<from><ackee count>|(<ackee address><sequence>)*|(<zero bits><to>|<message>)?
// 4 bytes    4bits  4bits          4 bits         4 bits        4 bits   4 bits  bytes*

// longest possible decoded message = 4 + 1 + 15 + 1 + 255 = 276
// longest possible encoded message = 368
// longest possible encoded message with start and end markers = 370

struct ffp_serialization_Packet {
    uint8_t from;
    uint16_t ackee_bitmask;
    uint8_t ackee_sequences[16];
    bool has_message;
    uint8_t to;
    
};

// no newline plz!!!
bool ffp_serialization_deserialize(struct ffp_serialization_Packet *dest, uint8_t *message_dest, uint8_t *raw_input, uint16_t raw_input_len);
