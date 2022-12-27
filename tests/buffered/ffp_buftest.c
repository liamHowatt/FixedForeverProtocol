#include "../../apis/buffered/ffp_buffered.h"

struct ffp_buftest {

};

void receive_message(struct buftest *self, uint8_t *, uint8_t) {

}

void tx_raw_data(struct buftest *self, uint8_t *, uint16_t) {

}

struct ffp_buffered_interface ffp_buftest_adapter = {
    .receive_message = ffp_buftest_receive_message_cb,
    .tx_raw_data = ffp_buftest_tx_raw_data
};
