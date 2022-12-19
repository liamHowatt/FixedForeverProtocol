import ctypes as ct
import random
from binascii import crc32

# system under test (sut)
sut = ct.CDLL("lib/crc32/ffe_crc32.so")

sut.ffe_crc32.argtypes = [ct.POINTER(ct.c_uint8), ct.c_uint32]
sut.ffe_crc32.restype = ct.c_uint32


randint = random.Random(42).randint

def Datagen():
    yield b''
    yield b'a'
    while True:
        yield bytes(randint(0, 255) for _ in range(randint(1, 1000)))
datagen = Datagen()

for _ in range(1000):
    data = next(datagen)
    buf = (len(data) * ct.c_uint8)(*data)
    assert crc32(data) == sut.ffe_crc32(buf, len(buf))