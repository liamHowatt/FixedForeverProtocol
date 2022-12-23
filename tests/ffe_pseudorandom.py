import ctypes as ct
from collections import defaultdict

# system under test (sut)
sut = ct.CDLL("lib/pseudorandom/ffp_pseudorandom.so")

sut.ffp_pseudorandom_lfsr_bit.argtypes = [ct.POINTER(ct.c_uint32)]
sut.ffp_pseudorandom_lfsr_bit.restype = ct.c_uint8

sut.ffp_pseudorandom_randint.argtypes = [ct.POINTER(ct.c_uint32), ct.c_uint16, ct.c_uint16]
sut.ffp_pseudorandom_randint.restype = ct.c_uint16

x = ct.c_uint32(0b1100_0000_0000_0000_0000_0000_0000_0011)
print(bin(x.value))
sut.ffp_pseudorandom_lfsr_bit(x)
print(bin(x.value))

zeros = 0
ones = 0
for _ in range(100_000):
    if sut.ffp_pseudorandom_lfsr_bit(x):
        ones += 1
    else:
        zeros += 1

print("zeros:", zeros)
print("ones:", ones)

d = defaultdict(int)
for _ in range(100_000):
    d[sut.ffp_pseudorandom_randint(x, 2, 15)] += 1

for x, c in sorted(d.items()):
    print(f"{x:<2}: {c}")