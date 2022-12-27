#pragma once

#include "../core/ffp_Core.hpp"

namespace ffp {
    
    class Buffered: Core {
        public:
        protected:
            virtual void receive_message(uint8_t *message, uint8_t len) = 0;
            virtual void tx(uint8_t *message, uint16_t len) = 0;

            void queue_message_to_send(uint8_t address, uint8_t *message, uint8_t len);
            bool can_queue_message(uint8_t len);
            void rx(uint8_t *message, uint16_t len);
        private:
            bool is_ready_to_tx_byte() override;
            bool tx_byte(uint8_t byte) override;
            bool is_ready_to_receive_decoded_byte() override;
            bool receive_decoded_byte(int16_t byte) override;
    };

}
