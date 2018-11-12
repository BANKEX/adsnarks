from sapling_jubjub import Point, Fq
from sapling_utils import i2lebsp
from ed25519 import publickey, signature, checkvalid

def toBinaryString(x):
    return ''.join(str(c) for c in i2lebsp(256, x))

if __name__ == "__main__":

    Bx = 17777552123799933955779906779655732241715742912184938656739573121738514868268 #4 * inv(5)
    By = 2626589144620713026669568689430873010625803728049924121243784502389097019475 #xrecover(By)

    base = Point(Fq(Bx), Fq(By))
        
    sk = "123123"
    pk = publickey(sk)

    value = 123

    m = hex(int(toBinaryString(value), 2))[2:]

    R, S = signature(m, sk, pk)

    checkvalid(R, S, m, pk)

    with open('keys/signature', 'w') as f:
        print(toBinaryString(S)[::-1], file = f)
        print(toBinaryString(value), file = f)
        print(toBinaryString(pk[0]), file = f)
        print(toBinaryString(pk[1]), file = f)
        print(toBinaryString(R[0]), file = f)
        print(toBinaryString(R[1]), file = f)