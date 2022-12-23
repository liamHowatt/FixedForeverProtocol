import ctypes as ct
from collections import deque
from random import Random
from math import ceil

# system under test (sut)
sut = ct.CDLL("lib/CircularBuffer/ffp_CircularBuffer.so")

class CbStruct(ct.Structure):
    _fields_ = [("mem_ptr", ct.POINTER(ct.c_uint8)),
                ("mem_size", ct.c_uint16),
                ("len", ct.c_uint16),
                ("first_out", ct.c_uint16)]

sut.ffp_CircularBuffer_init.argtypes = [ct.POINTER(CbStruct), ct.POINTER(ct.c_uint8), ct.c_uint16]
sut.ffp_CircularBuffer_init.restype = None

sut.ffp_CircularBuffer_enqueue.argtypes = [ct.POINTER(CbStruct), ct.c_uint8]
sut.ffp_CircularBuffer_enqueue.restype = None

sut.ffp_CircularBuffer_dequeue.argtypes = [ct.POINTER(CbStruct)]
sut.ffp_CircularBuffer_dequeue.restype = ct.c_uint8

# constant seed for reproducibility
randint = Random(42).randint


for mem_size in (0, 1, 2, 3, 4, 10, 3000, (2 ** 16) - 1):
    mem = (ct.c_uint8 * mem_size)()

    obj = CbStruct()
    sut.ffp_CircularBuffer_init(obj, mem, mem_size)

    # equivalent control (ctrl) data structure
    ctrl = deque(maxlen=mem_size)
    def ctrl_deq(ctrl):
        try:
            return ctrl.popleft()
        except IndexError:
            return 0
    def ctrl_enq(ctrl, x):
        ctrl.append(x)

    ENQ, DEQ = 1, 2

    for i in range(100):
        print(i)
        op = ENQ if randint(0, 1) else DEQ
        for _ in range(randint(min(1, mem_size), ceil(mem_size * 1.1))):
            if op == ENQ:
                x = randint(0, 255)
                ctrl_enq(ctrl, x)
                sut.ffp_CircularBuffer_enqueue(obj, x)
            else: # op == DEQ
                assert ctrl_deq(ctrl) == sut.ffp_CircularBuffer_dequeue(obj)
