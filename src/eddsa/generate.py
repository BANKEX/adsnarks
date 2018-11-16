import sys

from sapling_utils import i2lebsp
from ed25519 import publickey, signature, checkvalid
from random import randint

def toBinaryString(x):
    return ''.join(str(c) for c in i2lebsp(256, x))

def keypair():
    sk = hex(randint(16 ** 127, 16 ** 128 - 1))[2:]
    pk = publickey(sk)
    return sk, pk

def sign(value, sk):
    pk = publickey(sk)
    m = hex(int(toBinaryString(value), 2))[2:]
    R, S = signature(m, sk, pk)
    checkvalid(R, S, m, pk)
    return R, S

def verify(value, R, S, pk):
    m = hex(int(toBinaryString(value), 2))[2:]
    try:
        checkvalid(R, S, m, pk)
        return True
    except Exception as e:
        if e.args[0] == "signature does not pass verification":
            return False
        raise e

def represent(value, pk, R, S):
    return (toBinaryString(value),
            toBinaryString(pk[0]),
            toBinaryString(pk[1]),
            toBinaryString(R[0]),
            toBinaryString(R[1]),
            toBinaryString(S)[::-1])

if __name__ == "__main__":
    n = int(sys.argv[1])
    values = [randint(0, 2**16) for _ in range(n)]
    with open('keys/signature', 'w') as f:
        for value in values:
            sk, pk = keypair()
            R, S = sign(value, sk)
            for s in represent(value, pk, R, S):
                print(s, file = f)