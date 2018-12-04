import sys
from random import randint

from ethsnarks.jubjub import JUBJUB_L, Point, FQ
from ethsnarks.eddsa import eddsa_sign, eddsa_verify

from sapling_utils import i2lebsp



def toBinaryString(x):
    return ''.join(str(c) for c in i2lebsp(256, x))[:240]

def keypair():
    B = Point.from_hash(b'eddsa_base')  # base point
    k = FQ.random(JUBJUB_L)  # secret key
    A = B * k  # public key
    return k, A

def sign(value, k):
    k = FQ(k)
    B = Point.from_hash(b'eddsa_base')
    m = bytes.fromhex(hex(int(toBinaryString(value), 2))[2:])
    R, S, A = eddsa_sign(m, k, B)
    assert eddsa_verify(A, R, S, m, B)
    return R, S

def verify(value, R, S, A):
    R = Point(FQ(R[0]), FQ(R[1]))
    A = Point(FQ(A[0]), FQ(A[1]))
    B = Point.from_hash(b'eddsa_base')
    m = bytes.fromhex(hex(int(toBinaryString(value), 2))[2:])
    return eddsa_verify(A, R, S, m, B)

def represent(value, A, R, S):
    return (toBinaryString(value), A[0], A[1], R[0], R[1], S)

if __name__ == "__main__":
    n = int(sys.argv[1])
    values = [randint(0, 2**16) for _ in range(n)]
    with open('keys/signature', 'w') as f:
        for value in values:
            k, A = keypair()
            R, S = sign(value, k.n)
            for s in represent(value, [A.x.n, A.y.n], [R.x.n, R.y.n], S):
                print(s, file = f)