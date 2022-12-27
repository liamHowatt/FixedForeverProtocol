#include "../apis/buffered/ffp_Buffered.hpp"

namespace ffp {

    class BufferedTest: Buffered {
        public:
        protected:
        private:
            void receive_message(uint8_t *message, uint8_t len) override;
            void tx(uint8_t *message, uint16_t len) override;
    };

}
