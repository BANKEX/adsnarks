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

if __name__ == "__main__":
    value = 123
    sk, pk = keypair()
    R, S = sign(value, sk)
    with open('keys/signature', 'w') as f:
        print(toBinaryString(S)[::-1], file = f)
        print(toBinaryString(value), file = f)
        print(toBinaryString(pk[0]), file = f)
        print(toBinaryString(pk[1]), file = f)
        print(toBinaryString(R[0]), file = f)
        print(toBinaryString(R[1]), file = f)