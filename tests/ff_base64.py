import ctypes as ct
import base64
import string
import random

# system under test (sut)
sut = ct.CDLL("/root/ff/lib/base64/ff_base64.so")

sut.ff_base64_encoded_len_is_valid.argtypes = [ct.c_uint16]
sut.ff_base64_encoded_len_is_valid.restype = ct.c_bool

sut.ff_base64_encoded_len.argtypes = [ct.c_uint16]
sut.ff_base64_encoded_len.restype = ct.c_uint16

sut.ff_base64_decoded_len.argtypes = [ct.c_uint16]
sut.ff_base64_decoded_len.restype = ct.c_uint16

sut.ff_base64_encode.argtypes = [ct.POINTER(ct.c_uint8), ct.POINTER(ct.c_uint8), ct.c_uint16]
sut.ff_base64_encode.restype = None

sut.ff_base64_decode.argtypes = [ct.POINTER(ct.c_uint8), ct.POINTER(ct.c_uint8), ct.c_uint16]
sut.ff_base64_decode.restype = None


# encoded length is valid
for i in range(1000):
    assert sut.ff_base64_encoded_len_is_valid(len(base64.b64encode(b'0' * i).rstrip(b'=')))
assert sut.ff_base64_encoded_len_is_valid(len(b''))
assert not sut.ff_base64_encoded_len_is_valid(len(b'a'))
assert sut.ff_base64_encoded_len_is_valid(len(b'aa'))
assert sut.ff_base64_encoded_len_is_valid(len(b'aaa'))
assert sut.ff_base64_encoded_len_is_valid(len(b'aaaa'))
assert not sut.ff_base64_encoded_len_is_valid(len(b'aaaaa'))
assert sut.ff_base64_encoded_len_is_valid(len(b'aaaaaa'))


# encoded len and decoded len
for i in range(1000):
    de = b'0' * i
    en = base64.b64encode(de).rstrip(b'=')
    assert sut.ff_base64_encoded_len(len(de)) == len(en)
    assert sut.ff_base64_decoded_len(len(en)) == len(de)


# encode
b64_chars = string.ascii_uppercase + string.ascii_lowercase + string.digits + "+/"
assert len(b64_chars) == 64

def my_encode(data):
    ret = []
    for b in base64.b64encode(data).rstrip(b'='):
        ret.append(b64_chars.index(chr(b)) + 34)
    return bytes(ret)

randint = random.Random(42).randint

def Datagen():
    yield b''
    while True:
        yield bytes(randint(0, 255) for _ in range(randint(1, 1000)))
datagen = Datagen()

for _ in range(1000):
    data = next(datagen)
    dest = (ct.c_uint8 * sut.ff_base64_encoded_len(len(data)))()
    src = (ct.c_uint8 * len(data))(*data)
    sut.ff_base64_encode(dest, src, len(src))
    assert my_encode(data) == bytes(dest)


# decode
def my_decode(data):
    assert len(data) % 4 != 1
    to_decode = b''.join(
        b64_chars[b - 34].encode()
        for b
        in data
    )
    while len(to_decode) % 4:
        to_decode += b'='
    return base64.b64decode(to_decode)

def Datagen():
    yield b''
    while True:
        yield bytes(randint(0 + 34, 63 + 34) for _ in range(randint(1, 1000)))
datagen = Datagen()

for _ in range(1000):
    data = next(datagen)
    if len(data) % 4 == 1:
        data = data[:-1]
    dest = (ct.c_uint8 * sut.ff_base64_decoded_len(len(data)))()
    src = (ct.c_uint8 * len(data))(*data)
    sut.ff_base64_decode(dest, src, len(src))
    assert my_decode(data) == bytes(dest)
