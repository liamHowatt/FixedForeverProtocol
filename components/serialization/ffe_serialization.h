#pragma once

#include <stdint.h>

// no newline plz!!!
// return value of 0 means no message found
uint16_t ffe_serialization_locate_encoded_message(uint8_t raw_data, uint16_t raw_data_len);
