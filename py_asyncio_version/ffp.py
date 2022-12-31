import asyncio
from circular_buffer import CircularBuffer

class Ffp:
    def __init__(self,
        address,
        user_in_cb, # sync void (message)
        bus_out_cb, # sync void (bytes)
        user_out_buffer_size,
    ):
        self.address = address
        self.user_in_cb = user_in_cb
        self.bus_out_cb = bus_out_cb
        self.bus_in_buff = CircularBuffer(370)
        self.user_out_buffer = CircularBuffer(user_out_buffer_size)
        self.trying_to_send = None

    def can_user_out(self, message_len):
        if self.trying_to_send is None:
            return True
        return message_len <= (self.user_out_buffer.space_left() - 2)

    def user_out(self, address, message):
        if self.trying_to_send is None:
            self.trying_to_send = (address, message)
        elif len(message) <= (self.user_out_buffer.space_left() - 2):
            for b in message:
                self.user_out_buffer.enq(b)

    def bus_in(self, bytes):
        lf_index = bytes.find('\n')
        if lf_index == -1:
            for b in bytes:
                self.bus_in_buff.enq(b)
        else:
            
