#pragma once

#include <cstdint>

namespace ffp {

    class Core {
        public:
        protected:
            virtual bool is_ready_to_tx_byte() = 0;
            virtual bool tx_byte(uint8_t byte) = 0;
            virtual bool is_ready_to_receive_decoded_byte() = 0;
            virtual bool receive_decoded_byte(int16_t byte) = 0;

            bool is_ready_to_queue_byte_to_send();
            bool queue_byte_to_send(uint16_t byte);
            bool is_ready_to_rx_raw_byte();
            bool rx_raw_byte(uint8_t byte);
        private:
    };

}
