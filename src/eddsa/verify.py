import argparse

from generate import verify


int16 = lambda x: int(x, 16)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Verifies the signature on the value against the public key")
    parser.add_argument("value", type=int)
    parser.add_argument("R", help="point part of the signature", type=int16, nargs=2)
    parser.add_argument("S", help="scalar part of the signature", type=int16)
    parser.add_argument("pk", help="public key", type=int16, nargs=2)
    args = parser.parse_args()
    # print(args)
    print(verify(args.value, args.R, args.S, args.pk))