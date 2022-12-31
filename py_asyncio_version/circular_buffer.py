import array

class CircularBuffer:
    def __init__(self, size: int):
        self.arr = array.array('B', (0 for _ in range(size)))
        self.len = 0
        self.first_out = 0
    
    def enq(self, x: int) -> None:
        last_in = (self.first_out + self.len) % len(self.arr)
        self.arr[last_in] = x
        if self.len != len(self.arr):
            self.len += 1
        else:
            self.first_out = (self.first_out + 1) % len(self.arr)

    def deq(self) -> int:
        if not self.len:
            return 0
        ret = self.arr[self.first_out]
        self.first_out = (self.first_out + 1) % len(self.arr)
        self.len -= 1
        return ret

    def enqs(self, s: bytes) -> None:
        for b in s:
            self.enq(b)
    
    def deqs(self) -> bytes:
        def drain():
            while self.len:
                yield self.deq()
        return bytes(drain())

    def space_left(self) -> int:
        return len(self.arr) - self.len
