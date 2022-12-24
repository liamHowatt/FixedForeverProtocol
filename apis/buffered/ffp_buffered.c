#include "ffp_buffered.h"

bool ffp_buffered_is_ready_for_raw_tx_byte_cb(struct ffp_buffered *self) {

}

bool ffp_buffered_raw_tx_byte_cb(struct ffp_buffered *self, uint8_t byte) {

}

bool ffp_buffered_is_ready_to_actually_receive_byte_cb(struct ffp_buffered *self) {

}

bool ffp_buffered_actually_receive_byte_cb(struct ffp_buffered *self, uint8_t byte) {

}

struct ffp_core_interface ffp_buffered_adapter = {
    .is_ready_for_raw_tx_byte_cb = ffp_buffered_is_ready_for_raw_tx_byte_cb,
    .raw_tx_byte_cb = ffp_buffered_raw_tx_byte_cb,
    .is_ready_to_actually_receive_byte_cb = ffp_buffered_is_ready_to_actually_receive_byte_cb,
    .actually_receive_byte_cb = ffp_buffered_actually_receive_byte_cb,
};

void ffp_buffered_init(struct ffp_buffered *self) {
    ffp_core_init(&self->core, &ffp_buffered_adapter);
}


